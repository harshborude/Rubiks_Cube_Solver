const express = require('express');
const cors = require('cors');
const { spawn } = require('child_process');
const path = require('path');

const app = express();
const port = 3001;

app.use(cors());
app.use(express.json());

// Serve React frontend in production
const frontendDist = path.join(__dirname, '..', 'frontend', 'dist');
app.use(express.static(frontendDist));

// Path to the compiled C++ executable
const solverBin = process.platform === 'win32' ? 'rubiks_cube_solver.exe' : 'rubiks_cube_solver';
const solverPath = path.join(__dirname, '..', solverBin);
const projectRoot = path.join(__dirname, '..');

// Timeout for IDA* solve requests (30 seconds)
const SOLVE_TIMEOUT_MS = 30000;

// ---------------------------------------------------------------------------
// Persistent solver process
//
// The C++ binary is started ONCE in "server" mode. It loads the 50 MB pattern
// database on startup (~180 ms) and then waits for commands on stdin.
// Each command is one line; each response ends with a "DONE" line.
// This eliminates the per-request startup cost (was ~180 ms every call).
//
// Protocol:
//   stdin  → "scramble <depth>\n"           or  "solve <54chars> <algoId>\n"
//   stdout ← "MOVES: ...\nSTATE: ...\nDONE" or  "<moves>\nDONE"  (or "Error: ...\nDONE")
// ---------------------------------------------------------------------------

let solverProcess  = null;
let outputBuffer   = '';
let currentRequest = null;   // { input, resolve, reject } — request being processed
const requestQueue = [];     // pending requests, processed one at a time

function processNext() {
    if (currentRequest || requestQueue.length === 0 || !solverProcess) return;
    currentRequest = requestQueue.shift();
    solverProcess.stdin.write(currentRequest.input + '\n');
}

function deliverResponse(text) {
    const req = currentRequest;
    currentRequest = null;
    req.resolve(text);
    processNext();
}

function tryFlushResponse() {
    // Split on both \r\n (Windows) and \n (Linux/Mac)
    const lines = outputBuffer.split(/\r?\n/);
    const doneIdx = lines.findIndex(l => l === 'DONE');
    if (doneIdx === -1) return;

    const responseText = lines.slice(0, doneIdx).join('\n').trim();
    // Keep anything that arrived after DONE (shouldn't happen, but be safe)
    outputBuffer = lines.slice(doneIdx + 1).join('\n');
    deliverResponse(responseText);
}

function spawnSolverProcess() {
    console.log('Starting persistent solver process...');
    solverProcess = spawn(solverPath, ['server'], {
        cwd: projectRoot,
        stdio: ['pipe', 'pipe', 'pipe'],
    });

    solverProcess.stdout.setEncoding('utf8');
    solverProcess.stdout.on('data', (data) => {
        outputBuffer += data;
        tryFlushResponse();
    });

    solverProcess.stderr.on('data', (data) => {
        // The C++ process logs "Solver server ready" here — just print it
        console.log(`[solver] ${data.toString().trim()}`);
    });

    solverProcess.on('exit', (code, signal) => {
        console.warn(`Solver process exited (code=${code}, signal=${signal}). Restarting in 1 s...`);
        solverProcess = null;

        // Reject the in-flight request so the HTTP client gets an error immediately
        if (currentRequest) {
            currentRequest.reject(new Error(`Solver process exited unexpectedly (code=${code})`));
            currentRequest = null;
        }
        outputBuffer = '';

        setTimeout(() => {
            spawnSolverProcess();
            // Drain any requests that arrived while the process was down
            processNext();
        }, 1000);
    });

    console.log(`Solver process started (PID: ${solverProcess.pid})`);
    // Try to drain any requests queued before the process was ready
    processNext();
}

// Send a command to the solver and return a Promise that resolves with the
// response text (everything before the DONE line).  If timeoutMs elapses the
// request is rejected and the solver process is killed so it restarts cleanly.
function querySolver(input, timeoutMs = SOLVE_TIMEOUT_MS) {
    return new Promise((resolve, reject) => {
        let settled = false;

        function settle(fn, val) {
            if (settled) return;
            settled = true;
            clearTimeout(timer);
            fn(val);
        }

        const entry = {
            input,
            resolve: (val) => settle(resolve, val),
            reject:  (err) => settle(reject,  err),
        };

        const timer = setTimeout(() => {
            // Still waiting in queue — just remove it
            const idx = requestQueue.indexOf(entry);
            if (idx !== -1) {
                requestQueue.splice(idx, 1);
                settle(reject, new Error('Solver request timed out (was queued)'));
                return;
            }
            // Currently being processed — kill the process so it restarts
            if (currentRequest === entry) {
                currentRequest = null;
                outputBuffer = '';
                if (solverProcess) solverProcess.kill();
            }
            settle(reject, new Error('Solver timed out'));
        }, timeoutMs);

        if (!currentRequest && solverProcess) {
            // Process immediately
            currentRequest = entry;
            solverProcess.stdin.write(input + '\n');
        } else {
            // Solver busy or not yet ready — queue it
            requestQueue.push(entry);
        }
    });
}

// Start the solver process when the Node server loads
spawnSolverProcess();

// ---- SCRAMBLE ENDPOINT ----
app.get('/scramble', async (req, res) => {
    const depth = Math.min(Math.max(parseInt(req.query.depth) || 5, 1), 8);
    console.log(`Received scramble request with depth: ${depth}`);

    try {
        const output = await querySolver(`scramble ${depth}`, 10000);

        const lines = output.split('\n');
        let moves = '';
        let state = '';

        for (const line of lines) {
            if (line.startsWith('MOVES:')) moves = line.replace('MOVES:', '').trim();
            else if (line.startsWith('STATE:')) state = line.replace('STATE:', '').trim();
        }

        if (!state || state.length !== 54) {
            return res.status(500).json({ error: 'Invalid scramble output from solver', raw: output });
        }

        console.log(`Scramble generated: ${moves} -> ${state}`);
        res.json({
            success: true,
            moves: moves.split(' ').filter(m => m.length > 0),
            cubeState: state,
        });
    } catch (err) {
        console.error(`Scramble error: ${err.message}`);
        if (err.message.includes('timed out')) {
            return res.status(408).json({ error: 'Scramble timed out', details: err.message });
        }
        res.status(500).json({ error: 'Failed to generate scramble', details: err.message });
    }
});

// ---- SOLVE ENDPOINT ----
app.post('/solve', async (req, res) => {
    const { cubeState, algorithm } = req.body;

    if (!cubeState || cubeState.length !== 54) {
        return res.status(400).json({ error: 'Invalid cube state string. Must be 54 characters.' });
    }

    console.log(`Received solve request for state: ${cubeState} with algorithm: ${algorithm}`);

    // Map frontend algorithm strings to C++ numeric IDs
    // 1=IDA*  2=BFS  3=DFS  4=IDDFS
    let algoId = '1';
    if (algorithm === 'BFS')   algoId = '2';
    else if (algorithm === 'DFS')   algoId = '3';
    else if (algorithm === 'IDDFS') algoId = '4';

    try {
        const output = await querySolver(`solve ${cubeState} ${algoId}`, SOLVE_TIMEOUT_MS);

        if (output.includes('Error')) {
            return res.status(400).json({ error: 'Solver returned an error', details: output });
        }

        const movesArray = output ? output.split(' ').filter(m => m.length > 0) : [];
        console.log(`Solver output: ${output}`);

        res.json({ success: true, moves: movesArray, rawOutput: output });
    } catch (err) {
        console.error(`Solve error: ${err.message}`);
        if (err.message.includes('timed out')) {
            return res.status(408).json({
                error: 'Solver timed out. The cube state may be unsolvable or too complex.',
                details: 'The IDA* solver exceeded the time limit.',
            });
        }
        if (err.message.includes('exited unexpectedly')) {
            return res.status(500).json({
                error: 'Solver process crashed',
                details: err.message,
            });
        }
        res.status(500).json({ error: 'Failed to execute C++ solver', details: err.message });
    }
});

// SPA fallback — serve index.html for any unknown route
app.get('/{*splat}', (_req, res) => {
    res.sendFile(path.join(frontendDist, 'index.html'));
});

app.listen(port, () => {
    console.log(`Backend server listening at http://localhost:${port}`);
    console.log(`Expecting solver executable at: ${solverPath}`);
});
