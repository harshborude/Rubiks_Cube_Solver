const express = require('express');
const cors = require('cors');
const { execFile } = require('child_process');
const path = require('path');

const app = express();
const port = 3001;

app.use(cors());
app.use(express.json());

// Path to the compiled C++ executable
const solverPath = path.join(__dirname, '..', 'rubiks_cube_solver.exe'); 

// Timeout for the solver process (30 seconds)
const SOLVE_TIMEOUT_MS = 30000;

// ---- SCRAMBLE ENDPOINT ----
// Generates a valid scramble using the C++ code's randomShuffleCube()
app.get('/scramble', (req, res) => {
    const depth = parseInt(req.query.depth) || 5;
    const clampedDepth = Math.min(Math.max(depth, 1), 8); // Clamp 1-8 for IDA* to handle

    console.log(`Received scramble request with depth: ${clampedDepth}`);

    execFile(solverPath, ['scramble', String(clampedDepth)], { timeout: 10000 }, (error, stdout, stderr) => {
        if (error) {
            console.error(`Scramble error: ${error}`);
            return res.status(500).json({ error: 'Failed to generate scramble', details: error.message });
        }

        const lines = stdout.trim().split('\n');
        let moves = '';
        let state = '';

        for (const line of lines) {
            if (line.startsWith('MOVES:')) {
                moves = line.replace('MOVES:', '').trim();
            } else if (line.startsWith('STATE:')) {
                state = line.replace('STATE:', '').trim();
            }
        }

        if (!state || state.length !== 54) {
            return res.status(500).json({ error: 'Invalid scramble output from solver', raw: stdout });
        }

        console.log(`Scramble generated: ${moves} -> ${state}`);

        res.json({
            success: true,
            moves: moves.split(' ').filter(m => m.length > 0),
            cubeState: state,
        });
    });
});

// ---- SOLVE ENDPOINT ----
app.post('/solve', (req, res) => {
    const { cubeState, algorithm } = req.body;

    if (!cubeState || cubeState.length !== 54) {
        return res.status(400).json({ error: 'Invalid cube state string. Must be 54 characters.' });
    }

    console.log(`Received solve request for state: ${cubeState} with algorithm: ${algorithm}`);

    // Map frontend algorithm strings to C++ numeric IDs
    // 1 - IDA*, 2 - BFS, 3 - DFS, 4 - IDDFS
    let algoId = '1'; 
    if (algorithm === 'BFS') algoId = '2';
    else if (algorithm === 'DFS') algoId = '3';
    else if (algorithm === 'IDDFS') algoId = '4';

    // Call the C++ executable with the cube state string and the selected algorithm ID
    const child = execFile(solverPath, [cubeState, algoId], { timeout: SOLVE_TIMEOUT_MS }, (error, stdout, stderr) => {
        if (error) {
            if (error.killed) {
                console.error('Solver timed out after 30 seconds.');
                return res.status(408).json({ 
                    error: 'Solver timed out. The cube state may be unsolvable or too complex.',
                    details: 'The IDA* solver exceeded the 30-second time limit.'
                });
            }
            console.error(`Execution error: ${error}`);
            return res.status(500).json({ 
                error: 'Failed to execute C++ solver', 
                details: error.message,
                stderr: stderr
            });
        }
        
        if (stderr) {
            console.warn(`Solver stderr: ${stderr}`);
        }

        const movesOutput = stdout.trim();
        console.log(`Solver output: ${movesOutput}`);
        
        // If output contains "Error", it's a real error
        if (movesOutput.includes("Error")) {
             return res.status(400).json({ error: 'Solver returned an error', details: movesOutput });
        }

        // Empty output means the cube is already solved (0 moves needed)
        const movesArray = movesOutput ? movesOutput.split(' ').filter(m => m.length > 0) : [];

        res.json({
            success: true,
            moves: movesArray,
            rawOutput: movesOutput,
        });
    });
});

app.listen(port, () => {
    console.log(`Backend server listening at http://localhost:${port}`);
    console.log(`Expecting solver executable at: ${solverPath}`);
});
