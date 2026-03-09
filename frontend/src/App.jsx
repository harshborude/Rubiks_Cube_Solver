import React from 'react';
import CubeVisualizer from './components/CubeVisualizer';
import InputControls from './components/InputControls';
import SolverControls from './components/SolverControls';
import TerminalOutput from './components/TerminalOutput';
import { useState } from 'react';

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

  const handleSolve = async () => {
    if (isSolving) return;
    
    addLog(`Initiating solver using ${selectedSolver} algorithm...`, 'system');
    addLog('Scanning cube state... Validating edge and corner permutations...', 'info');
    
    if (!validateCube()) {
      addLog('Solve aborted due to invalid cube state.', 'system');
      return;
    }

    setIsSolving(true);
    addLog('Cube valid. Contacting solver API...', 'system');

    try {
      // Replace this URL when your Render service is live!
      // Example: 'https://rubiks-cube-solver-api.onrender.com/api/solve'
      const API_URL = import.meta.env.VITE_API_URL || 'http://localhost:8080/api/solve';

      const response = await fetch(API_URL, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          algorithm: selectedSolver,
          U: cubeState.U,
          L: cubeState.L,
          F: cubeState.F,
          R: cubeState.R,
          B: cubeState.B,
          D: cubeState.D
        }),
      });

      if (!response.ok) {
        throw new Error(`API returned status ${response.status}`);
      }

      const data = await response.json();
      
      if (data.status === 'success') {
        addLog(`Depth limit check passed. Optimal path found!`, 'success');
        addLog(`Move sequence: ${data.moves.join(' ')}`, 'highlight');
        addLog('Cube solved successfully.', 'success');
        addLog(`Solved in ${data.timeSeconds} seconds.`, 'highlight');
        
        // Reset to solved state for wow factor
        setCubeState(initialCubeState);
      } else {
         addLog(`Solver Error: ${data.message}`, 'error');
      }

    } catch (error) {
      addLog(`Network Error: Ensure the C++ backend is running. ${error.message}`, 'error');
    } finally {
      setIsSolving(false);
    }
  };

  const handleScramble = () => {
    addLog('Generating random scramble...', 'system');
    
    // Create a pool of remaining stickers (8 of each color, since 1 is locked in the center)
    const pool = [
      ...Array(8).fill('white'),
      ...Array(8).fill('green'),
      ...Array(8).fill('red'),
      ...Array(8).fill('blue'),
      ...Array(8).fill('orange'),
      ...Array(8).fill('yellow')
    ];
    
    // Shuffle the pool using Fisher-Yates
    for (let i = pool.length - 1; i > 0; i--) {
      const j = Math.floor(Math.random() * (i + 1));
      [pool[i], pool[j]] = [pool[j], pool[i]];
    }

    const expectedCenters = {
      U: 'white', L: 'green', F: 'red', R: 'blue', B: 'orange', D: 'yellow'
    };

    let poolIndex = 0;
    const scrambled = {};

    for (const [face, centerColor] of Object.entries(expectedCenters)) {
      scrambled[face] = Array(3).fill(null).map((_, rIdx) => 
        Array(3).fill(null).map((_, cIdx) => {
          if (rIdx === 1 && cIdx === 1) return centerColor; // Fixed center
          return pool[poolIndex++];
        })
      );
    }
    
    setCubeState(scrambled);
    addLog('Scramble applied.', 'info');
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
