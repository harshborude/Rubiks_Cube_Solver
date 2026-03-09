import React, { useState } from 'react';
import { Camera, Shuffle, Keyboard } from 'lucide-react';

const InputControls = ({ onScramble, addLog, setCubeState }) => {
  const [activeTab, setActiveTab] = useState('scramble');

  const handleScanClick = () => {
    setActiveTab('scan');
    addLog('Initializing camera feed...', 'system');
    setTimeout(() => addLog('Error: Camera permissions not granted or webcam unavailable. Cannot scan physical cube.', 'error'), 1500);
  };

  const handleManualClick = () => {
    setActiveTab('manual');
    addLog('Manual input mode active. Click on a face square in the visualizer to change its color.', 'info');
  };

  const handleScrambleClick = () => {
    setActiveTab('scramble');
    onScramble();
  };

  return (
    <div className="glass-panel w-full p-4 md:p-6 drop-shadow-lg">
      <h2 className="text-xl font-semibold mb-4 text-slate-200">Input Method</h2>
      
      <div className="flex bg-slate-800/50 p-1 rounded-xl w-full max-w-sm mb-6 shadow-inner ring-1 ring-white/5">
        <button
          onClick={handleScanClick}
          className={`flex-1 py-2 px-3 text-sm font-medium rounded-lg flex items-center justify-center gap-2 transition-all ${activeTab === 'scan' ? 'bg-indigo-500 shadow-md text-white' : 'text-slate-400 hover:text-slate-200 hover:bg-white/5'}`}
        >
          <Camera size={16} /> Scan
        </button>
        <button
          onClick={handleScrambleClick}
          className={`flex-1 py-2 px-3 text-sm font-medium rounded-lg flex items-center justify-center gap-2 transition-all ${activeTab === 'scramble' ? 'bg-indigo-500 shadow-md text-white' : 'text-slate-400 hover:text-slate-200 hover:bg-white/5'}`}
        >
          <Shuffle size={16} /> Random
        </button>
        <button
          onClick={handleManualClick}
          className={`flex-1 py-2 px-3 text-sm font-medium rounded-lg flex items-center justify-center gap-2 transition-all ${activeTab === 'manual' ? 'bg-indigo-500 shadow-md text-white' : 'text-slate-400 hover:text-slate-200 hover:bg-white/5'}`}
        >
          <Keyboard size={16} /> Manual
        </button>
      </div>

      <div className="text-sm text-slate-400 min-h-[40px]">
        {activeTab === 'scan' && <p>Hold your Rubik's Cube to the camera to automatically detect its current state.</p>}
        {activeTab === 'scramble' && <p>Click the Random tab again to generate a new shuffled state.</p>}
        {activeTab === 'manual' && <p>Type keyboard keys (w, b, g, r, o, y) or click grid colors to set faces manually.</p>}
      </div>
    </div>
  );
};

export default InputControls;
