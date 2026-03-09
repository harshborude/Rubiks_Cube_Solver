import React from 'react';

const CubeVisualizer = ({ cubeState, setCubeState }) => {

  const colorMap = {
    white: 'bg-white',
    red: 'bg-red-500',
    blue: 'bg-blue-500',
    orange: 'bg-orange-500',
    green: 'bg-green-500',
    yellow: 'bg-yellow-400',
  };

  const renderFace = (faceKey, label) => {
    return (
      <div className="flex flex-col items-center gap-1">
        <span className="text-xs font-bold text-slate-400 select-none uppercase tracking-widest">{label}</span>
        <div className="grid grid-cols-3 gap-1 bg-slate-950 p-1 rounded-md border-2 border-slate-700 shadow-inner">
          {cubeState[faceKey].map((row, rIdx) =>
            row.map((color, cIdx) => (
              <div
                key={`${faceKey}-${rIdx}-${cIdx}`}
                className={`w-8 h-8 md:w-10 md:h-10 rounded-sm border border-black/20 shadow-sm ${colorMap[color]} transition-colors duration-300 hover:brightness-110 cursor-pointer`}
                title={`Face: ${label}, Row: ${rIdx}, Col: ${cIdx}`}
              />
            ))
          )}
        </div>
      </div>
    );
  };

  return (
    <div className="glass-panel p-6 md:p-8 flex flex-col items-center w-full max-w-2xl overflow-x-auto">
      <div className="grid grid-cols-4 gap-4 md:gap-6 min-w-[max-content]">
        {/* Row 1 */}
        <div className="col-start-2">{renderFace('U', 'Up')}</div>
        
        {/* Row 2 */}
        <div className="col-start-1">{renderFace('L', 'Left')}</div>
        <div className="col-start-2">{renderFace('F', 'Front')}</div>
        <div className="col-start-3">{renderFace('R', 'Right')}</div>
        <div className="col-start-4">{renderFace('B', 'Back')}</div>
        
        {/* Row 3 */}
        <div className="col-start-2">{renderFace('D', 'Down')}</div>
      </div>
    </div>
  );
};

export default CubeVisualizer;
