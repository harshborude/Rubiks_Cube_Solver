import React from 'react';
import axios from 'axios';
import CubeVisualizer from './components/CubeVisualizer';
import InputControls from './components/InputControls';
import SolverControls from './components/SolverControls';
import TerminalOutput from './components/TerminalOutput';
import { useState } from 'react';

// Map frontend color names to C++ single-character codes
const colorToChar = {
  white: 'W',
  green: 'G',
  red: 'R',
  blue: 'B',
  orange: 'O',
  yellow: 'Y',
};

// C++ FACE enum order: UP(0), LEFT(1), FRONT(2), RIGHT(3), BACK(4), DOWN(5)
const faceOrder = ['U', 'L', 'F', 'R', 'B', 'D'];

const BACKEND_URL = import.meta.env.DEV ? 'http://localhost:3001' : '';

// Default solved state
const initializeFace = (color) => Array(3).fill(null).map(() => Array(3).fill(color));

const initialCubeState = {
  U: initializeFace('white'),
  L: initializeFace('green'),
  F: initializeFace('red'),
  R: initializeFace('blue'),
  B: initializeFace('orange'),
  D: initializeFace('yellow'),
};

function App() {
  const [cubeState, setCubeState] = useState(initialCubeState);
  const [terminalLogs, setTerminalLogs] = useState([{ type: 'system', text: 'Ready. Waiting for input...' }]);
  const [isSolving, setIsSolving] = useState(false);
  const [selectedSolver, setSelectedSolver] = useState('IDA*');
  const [inputMode, setInputMode] = useState('scramble');
  
  const addLog = (text, type = 'info') => {
    setTerminalLogs(prev => [...prev, { text, type }]);
  };

  const validateCube = () => {
    // 1. Check Centers
    const expectedCenters = {
      U: 'white',
      L: 'green',
      F: 'red',
      R: 'blue',
      B: 'orange',
      D: 'yellow'
    };

    for (const [face, expectedColor] of Object.entries(expectedCenters)) {
      if (cubeState[face][1][1] !== expectedColor) {
        addLog(`Validation Error: The center piece of the ${face} face must be ${expectedColor}.`, 'error');
        return false;
      }
    }

    // 2. Count Colors
    const colorCounts = {
      white: 0,
      green: 0,
      red: 0,
      blue: 0,
      orange: 0,
      yellow: 0
    };

    let total = 0;
    for (const face of Object.values(cubeState)) {
      for (const row of face) {
        for (const color of row) {
          if (colorCounts[color] !== undefined) {
            colorCounts[color]++;
            total++;
          }
        }
      }
    }

    const invalidColors = Object.entries(colorCounts).filter(([_, count]) => count !== 9);
    
    if (invalidColors.length > 0) {
      addLog(`Validation Error: Invalid color distribution. Each color must appear exactly 9 times.`, 'error');
      invalidColors.forEach(([color, count]) => {
        addLog(`- ${color} appears ${count} times (expected 9)`, 'error');
      });
      return false;
    }

    return true;
  };

  // Convert the 2D array cube state into a 54-character string for the C++ solver
  const cubeStateToString = () => {
    let str = '';
    for (const face of faceOrder) {
      for (let row = 0; row < 3; row++) {
        for (let col = 0; col < 3; col++) {
          const color = cubeState[face][row][col];
          const char = colorToChar[color];
          if (!char) {
            addLog(`Error: Unknown color '${color}' at face ${face} [${row}][${col}]`, 'error');
            return null; // Return null to indicate encoding failure
          }
          str += char;
        }
      }
    }
    return str;
  };

  const handleSolve = async () => {
    if (isSolving) return;
    
    addLog(`Initiating solver using ${selectedSolver} algorithm...`, 'system');
    addLog('Scanning cube state... Validating edge and corner permutations...', 'info');
    
    if (!validateCube()) {
      addLog('Solve aborted due to invalid cube state.', 'system');
      return;
    }

    setIsSolving(true);
    
    const cubeString = cubeStateToString();
    if (!cubeString) {
      addLog('Solve aborted due to encoding error.', 'system');
      setIsSolving(false);
      return;
    }

    addLog(`Cube state encoded: ${cubeString}`, 'info');
    addLog('Sending to C++ solver backend...', 'info');

    try {
      const startTime = performance.now();
      const response = await axios.post(`${BACKEND_URL}/solve`, {
        cubeState: cubeString,
        algorithm: selectedSolver,
      });
      const endTime = performance.now();
      const duration = ((endTime - startTime) / 1000).toFixed(4);

      if (response.data.success) {
        const moves = response.data.moves;
        addLog(`Solution found! ${moves.length} moves.`, 'success');
        addLog(`Move sequence: ${moves.join(' ')}`, 'highlight');
        addLog(`Solved in ${duration} seconds (round-trip).`, 'highlight');
        setCubeState(initialCubeState);
      } else {
        addLog(`Solver error: ${response.data.error}`, 'error');
      }
    } catch (err) {
      addLog(`Backend error: ${err.message}`, 'error');
      if (err.response?.data?.details) {
        addLog(`Details: ${err.response.data.details}`, 'error');
      }
    } finally {
      setIsSolving(false);
    }
  };

  // Map C++ single-character codes back to frontend color names
  const charToColor = {
    W: 'white',
    G: 'green',
    R: 'red',
    B: 'blue',
    O: 'orange',
    Y: 'yellow',
  };

  // Parse a 54-char state string from the backend into the 2D array cubeState format
  const parseStateString = (stateStr) => {
    const parsed = {};
    for (let f = 0; f < faceOrder.length; f++) {
      const face = faceOrder[f];
      parsed[face] = Array(3).fill(null).map((_, row) =>
        Array(3).fill(null).map((_, col) => {
          const idx = f * 9 + row * 3 + col;
          return charToColor[stateStr[idx]] || 'white';
        })
      );
    }
    return parsed;
  };

  const handleScramble = async () => {
    addLog('Generating random scramble via C++ backend...', 'system');
    
    try {
      const response = await axios.get(`${BACKEND_URL}/scramble`, {
        params: { depth: 5 }
      });

      if (response.data.success) {
        const newState = parseStateString(response.data.cubeState);
        setCubeState(newState);
        addLog(`Scramble moves: ${response.data.moves.join(' ')}`, 'info');
        addLog('Valid scramble applied.', 'info');
      } else {
        addLog('Scramble failed.', 'error');
      }
    } catch (err) {
      addLog(`Scramble error: ${err.message}`, 'error');
    }
  };

  return (
    <div className="min-h-screen p-4 md:p-8 flex flex-col items-center justify-start gap-8 max-w-7xl mx-auto">
      <header className="text-center space-y-2 mb-4">
        <h1 className="text-4xl md:text-5xl font-extrabold tracking-tight bg-gradient-to-r from-blue-400 to-indigo-500 bg-clip-text text-transparent">
          Rubik's Cube Solver
        </h1>
        <p className="text-slate-400 font-medium">Configure your cube and find the optimal solution instantly.</p>
      </header>

      <div className="w-full grid grid-cols-1 lg:grid-cols-12 gap-8 items-start">
        {/* Left/Top Column: Visualizer */}
        <div className="lg:col-span-7 w-full flex justify-center">
          <CubeVisualizer 
            cubeState={cubeState} 
            setCubeState={setCubeState} 
            inputMode={inputMode}
          />
        </div>

        {/* Right/Bottom Column: Controls */}
        <div className="lg:col-span-5 w-full flex flex-col gap-6">
          <InputControls 
            onScramble={handleScramble} 
            addLog={addLog} 
            setCubeState={setCubeState} 
            inputMode={inputMode}
            setInputMode={setInputMode}
          />
          
          <SolverControls 
            selectedSolver={selectedSolver} 
            setSelectedSolver={setSelectedSolver} 
            onSolve={handleSolve} 
            isSolving={isSolving} 
          />
        </div>
      </div>

      {/* Terminal Full Width Bottom */}
      <div className="w-full mt-4">
        <TerminalOutput logs={terminalLogs} />
      </div>
    </div>
  );
}

export default App;
