import React, { useEffect, useRef } from 'react';
import { Terminal } from 'lucide-react';

const TerminalOutput = ({ logs }) => {
  const endRef = useRef(null);

  useEffect(() => {
    endRef.current?.scrollIntoView({ behavior: 'smooth' });
  }, [logs]);

  const getLogStyle = (type) => {
    switch (type) {
      case 'error': return 'text-red-400';
      case 'success': return 'text-green-400';
      case 'highlight': return 'text-yellow-300 font-bold';
      case 'system': return 'text-slate-500 italic';
      default: return 'text-slate-300';
    }
  };

  return (
    <div className="w-full h-64 bg-[#0a0f1c] rounded-xl border border-slate-800 shadow-2xl flex flex-col overflow-hidden font-mono text-sm leading-relaxed relative ring-1 ring-white/5">
      
      {/* Terminal Header */}
      <div className="bg-slate-900/80 backdrop-blur-sm border-b border-slate-800 px-4 py-2 flex items-center justify-between z-10 sticky top-0">
        <div className="flex items-center gap-2 text-slate-400">
          <Terminal size={14} />
          <span className="text-xs tracking-wider uppercase">Solver Console</span>
        </div>
        <div className="flex gap-1.5">
          <div className="w-3 h-3 rounded-full bg-slate-700 hover:bg-red-500 transition-colors cursor-pointer"></div>
          <div className="w-3 h-3 rounded-full bg-slate-700 hover:bg-yellow-500 transition-colors cursor-pointer"></div>
          <div className="w-3 h-3 rounded-full bg-slate-700 hover:bg-green-500 transition-colors cursor-pointer"></div>
        </div>
      </div>

      {/* Terminal Body */}
      <div className="flex-1 p-4 overflow-y-auto w-full selection:bg-indigo-500/40">
        {logs.map((log, index) => (
          <div key={index} className={`mb-1 break-words ${getLogStyle(log.type)}`}>
            {log.type !== 'system' && (
              <span className="text-indigo-400/50 mr-2 select-none">~{'>'}</span>
            )}
            {log.text}
          </div>
        ))}
        <div ref={endRef} />
      </div>
      
    </div>
  );
};

export default TerminalOutput;
