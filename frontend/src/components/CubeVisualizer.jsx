import React from 'react';

const CubeVisualizer = ({ cubeState, setCubeState, inputMode }) => {

  const COLORS = ['white', 'red', 'blue', 'orange', 'green', 'yellow'];
  const colorMap = {
    white: 'bg-white',
    red: 'bg-red-500',
    blue: 'bg-blue-500',
    orange: 'bg-orange-500',
    green: 'bg-green-500',
    yellow: 'bg-yellow-400',
  };

  const handleSquareClick = (faceKey, rIdx, cIdx, currentColor) => {
    if (inputMode !== 'manual') return;
    
    // Prevent changing the center piece
    if (rIdx === 1 && cIdx === 1) return;

    // Cycle to the next color in the array
    const currentIndex = COLORS.indexOf(currentColor);
    const nextColor = COLORS[(currentIndex + 1) % COLORS.length];

    setCubeState(prevState => {
      const newState = { ...prevState };
      newState[faceKey] = [
        [...prevState[faceKey][0]],
        [...prevState[faceKey][1]],
        [...prevState[faceKey][2]],
      ];
      newState[faceKey][rIdx][cIdx] = nextColor;
      return newState;
    });
  };

  const setSquareColor = (faceKey, rIdx, cIdx, newColor) => {
    if (rIdx === 1 && cIdx === 1) return; // Prevent center changes
    setCubeState(prevState => {
      const newState = { ...prevState };
      newState[faceKey] = [
        [...prevState[faceKey][0]],
        [...prevState[faceKey][1]],
        [...prevState[faceKey][2]],
      ];
      newState[faceKey][rIdx][cIdx] = newColor;
      return newState;
    });
  };

  const handleKeyDown = (e, faceKey, rIdx, cIdx) => {
    if (inputMode !== 'manual') return;
    
    const keyMap = {
      'w': 'white',
      'r': 'red',
      'b': 'blue',
      'o': 'orange',
      'g': 'green',
      'y': 'yellow'
    };

    const newColor = keyMap[e.key.toLowerCase()];
    if (newColor) {
      setSquareColor(faceKey, rIdx, cIdx, newColor);
    }
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
                tabIndex={inputMode === 'manual' && !(rIdx === 1 && cIdx === 1) ? 0 : -1}
                onClick={() => handleSquareClick(faceKey, rIdx, cIdx, color)}
                onKeyDown={(e) => handleKeyDown(e, faceKey, rIdx, cIdx)}
                className={`w-8 h-8 md:w-10 md:h-10 rounded-sm border border-black/20 shadow-sm transition-colors duration-200 ${colorMap[color]} ${inputMode === 'manual' && !(rIdx === 1 && cIdx === 1) ? 'cursor-pointer hover:brightness-110 hover:scale-105 active:scale-95 focus:outline-none focus:ring-2 focus:ring-indigo-500 focus:scale-110 z-10' : 'outline-none'}`}
                title={`Face: ${label}${rIdx === 1 && cIdx === 1 ? ' (Center fixed)' : ''}`}
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
