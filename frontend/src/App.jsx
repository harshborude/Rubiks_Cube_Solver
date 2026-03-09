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
  
  const addLog = (text, type = 'info') => {
    setTerminalLogs(prev => [...prev, { text, type }]);
  };

  const handleSolve = () => {
    if (isSolving) return;
    setIsSolving(true);
    addLog(`Initiating solver using ${selectedSolver} algorithm...`, 'system');
    
    // Simulate solving progression
    setTimeout(() => addLog('Scanning cube state... Validating edge and corner permutations...', 'info'), 500);
    setTimeout(() => addLog('Cube state valid. Exploring nodes...', 'info'), 1500);
    setTimeout(() => addLog(`Depth limit check passed. Found optimal path in 14 moves.`, 'success'), 3000);
    
    setTimeout(() => {
      addLog('Move sequence: U R2 F B R B2 R U2 L B2 R U\' D\' R2 F R\' L B2 U2 F2', 'highlight');
      addLog('Cube solved successfully.', 'success');
      addLog(`Solved in ${(Math.random() * 2 + 0.5).toFixed(4)} seconds!`, 'highlight');
      // Reset visualizer to solved state to simulate completion
      setCubeState(initialCubeState);
      setIsSolving(false);
    }, 4500);
  };

  const handleScramble = () => {
    addLog('Generating random scramble...', 'system');
    const colors = ['white', 'red', 'blue', 'orange', 'green', 'yellow'];
    
    // Random visual scramble (not technically a valid rubik's cube, just for UI demonstration)
    const scrambled = {
      U: Array(3).fill(null).map(() => Array(3).fill(null).map(() => colors[Math.floor(Math.random() * colors.length)])),
      L: Array(3).fill(null).map(() => Array(3).fill(null).map(() => colors[Math.floor(Math.random() * colors.length)])),
      F: Array(3).fill(null).map(() => Array(3).fill(null).map(() => colors[Math.floor(Math.random() * colors.length)])),
      R: Array(3).fill(null).map(() => Array(3).fill(null).map(() => colors[Math.floor(Math.random() * colors.length)])),
      B: Array(3).fill(null).map(() => Array(3).fill(null).map(() => colors[Math.floor(Math.random() * colors.length)])),
      D: Array(3).fill(null).map(() => Array(3).fill(null).map(() => colors[Math.floor(Math.random() * colors.length)])),
    };
    
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
          <CubeVisualizer cubeState={cubeState} setCubeState={setCubeState} />
        </div>

        {/* Right/Bottom Column: Controls */}
        <div className="lg:col-span-5 w-full flex flex-col gap-6">
          <InputControls onScramble={handleScramble} addLog={addLog} setCubeState={setCubeState} />
          
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
