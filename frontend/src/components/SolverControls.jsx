import React from 'react';
import { Play, Activity } from 'lucide-react';

const SolverControls = ({ selectedSolver, setSelectedSolver, onSolve, isSolving }) => {
  return (
    <div className="glass-panel w-full p-4 md:p-6 drop-shadow-lg flex flex-col gap-5">
      <div className="flex flex-col gap-2">
        <label htmlFor="solver-select" className="text-sm font-semibold text-slate-300 flex items-center gap-2">
          <Activity size={16} className="text-indigo-400"/> Choose Solver Algorithm
        </label>
        <div className="relative">
          <select
            id="solver-select"
            value={selectedSolver}
            onChange={(e) => setSelectedSolver(e.target.value)}
            disabled={isSolving}
            className="w-full bg-slate-800 text-slate-100 placeholder-slate-400 border border-slate-700 outline-none rounded-xl py-3 px-4 appearance-none focus:ring-2 focus:ring-indigo-500 focus:border-indigo-500 transition-shadow disabled:opacity-50"
          >
            <option value="IDA*">IDA* (Iterative Deepening A*)</option>
            <option value="BFS">BFS (Breadth-First Search)</option>
            <option value="DFS">DFS (Depth-First Search)</option>
            <option value="IDDFS">IDDFS (Iterative Deepening DFS)</option>
          </select>
          <div className="pointer-events-none absolute inset-y-0 right-0 flex items-center px-4 text-slate-400">
            <svg className="fill-current h-4 w-4" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 20 20">
              <path d="M9.293 12.95l.707.707L15.657 8l-1.414-1.414L10 10.828 5.757 6.586 4.343 8z" />
            </svg>
          </div>
        </div>
      </div>

      <button
        onClick={onSolve}
        disabled={isSolving}
        className="w-full mt-2 relative overflow-hidden group bg-gradient-to-br from-indigo-500 to-purple-600 font-bold text-white shadow-lg shadow-indigo-500/30 rounded-xl py-4 flex justify-center items-center gap-2 transition-all hover:scale-[1.02] hover:shadow-indigo-500/50 active:scale-95 disabled:opacity-50 disabled:pointer-events-none"
      >
        <div className="absolute inset-0 bg-white/20 translate-y-full group-hover:translate-y-0 transition-transform duration-300 ease-out"></div>
        {isSolving ? (
          <><div className="w-5 h-5 border-2 border-white/30 border-t-white rounded-full animate-spin"></div> Solving...</>
        ) : (
          <><Play size={20} fill="currentColor" /> Solve Cube</>
        )}
      </button>
    </div>
  );
};

export default SolverControls;
