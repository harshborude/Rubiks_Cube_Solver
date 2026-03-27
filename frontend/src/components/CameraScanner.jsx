import React, { useRef, useEffect, useState, useCallback } from 'react';

// Face scan order matching C++ FACE enum: U(0), L(1), F(2), R(3), B(4), D(5)
const FACE_ORDER = ['U', 'L', 'F', 'R', 'B', 'D'];

const FACE_INFO = {
  U: { label: 'Top (U)',    center: 'white',  color: '#ffffff', instruction: 'Hold cube with the WHITE center facing the camera' },
  L: { label: 'Left (L)',   center: 'green',  color: '#22c55e', instruction: 'Rotate cube — GREEN center facing the camera' },
  F: { label: 'Front (F)',  center: 'red',    color: '#ef4444', instruction: 'RED center facing the camera' },
  R: { label: 'Right (R)',  center: 'blue',   color: '#3b82f6', instruction: 'BLUE center facing the camera' },
  B: { label: 'Back (B)',   center: 'orange', color: '#f97316', instruction: 'ORANGE center facing the camera' },
  D: { label: 'Bottom (D)', center: 'yellow', color: '#eab308', instruction: 'YELLOW center facing the camera' },
};

const COLOR_DISPLAY = {
  white:  '#ffffff',
  green:  '#22c55e',
  red:    '#ef4444',
  blue:   '#3b82f6',
  orange: '#f97316',
  yellow: '#eab308',
};

// Box size in pixels (matches CubeScanner.cpp default boxSize=60)
const BOX_SIZE = 60;
const GRID_SIZE = BOX_SIZE * 3; // 180px

// ---- Color classification (JS port of CubeScanner.cpp classifyColor) ----
// CubeScanner uses OpenCV HSV where H is 0-180 (half of standard 0-360)

function rgbToOpenCvH(r, g, b) {
  r /= 255; g /= 255; b /= 255;
  const max = Math.max(r, g, b);
  const min = Math.min(r, g, b);
  const diff = max - min;
  if (diff === 0) return 0;
  let h = 0;
  if (max === r)      h = 60 * (((g - b) / diff) % 6);
  else if (max === g) h = 60 * ((b - r) / diff + 2);
  else                h = 60 * ((r - g) / diff + 4);
  if (h < 0) h += 360;
  return h / 2; // OpenCV H range: 0-180
}

function classifyColor(r, g, b) {
  // White: all channels > 200, all similar (same logic as C++)
  if (r > 200 && g > 200 && b > 200 &&
      Math.abs(r - g) < 30 && Math.abs(g - b) < 30 && Math.abs(r - b) < 30)
    return 'white';

  const h = rgbToOpenCvH(r, g, b);
  if (h >= 160 || h < 3)    return 'red';    // red wraps around 180
  if (h >= 3  && h <= 19)   return 'orange';
  if (h >= 20 && h <= 30)   return 'yellow';
  if (h >= 60 && h <= 90)   return 'green';
  if (h >= 100 && h <= 120) return 'blue';
  return 'white'; // fallback (same as C++)
}

// Median of a 5x5 pixel region centered on (cx, cy) — mirrors medianColor() in C++
function medianColor(imageData, cx, cy, width, height, region = 5) {
  const half = Math.floor(region / 2);
  const Rs = [], Gs = [], Bs = [];
  for (let dy = -half; dy <= half; dy++) {
    for (let dx = -half; dx <= half; dx++) {
      const x = Math.min(Math.max(cx + dx, 0), width - 1);
      const y = Math.min(Math.max(cy + dy, 0), height - 1);
      const idx = (y * width + x) * 4;
      Rs.push(imageData.data[idx]);
      Gs.push(imageData.data[idx + 1]);
      Bs.push(imageData.data[idx + 2]);
    }
  }
  Rs.sort((a, b) => a - b);
  Gs.sort((a, b) => a - b);
  Bs.sort((a, b) => a - b);
  const mid = Math.floor(Rs.length / 2);
  return [Rs[mid], Gs[mid], Bs[mid]];
}

// Extract 3x3 grid of colors from the center of a canvas frame
function extractFaceColors(canvas) {
  const ctx = canvas.getContext('2d');
  const { width, height } = canvas;
  const imageData = ctx.getImageData(0, 0, width, height);

  const startX = Math.floor((width - GRID_SIZE) / 2);
  const startY = Math.floor((height - GRID_SIZE) / 2);

  const face = [];
  for (let row = 0; row < 3; row++) {
    const rowColors = [];
    for (let col = 0; col < 3; col++) {
      const cx = startX + col * BOX_SIZE + Math.floor(BOX_SIZE / 2);
      const cy = startY + row * BOX_SIZE + Math.floor(BOX_SIZE / 2);
      const [r, g, b] = medianColor(imageData, cx, cy, width, height);
      rowColors.push(classifyColor(r, g, b));
    }
    face.push(rowColors);
  }
  return face;
}

// Draw 3x3 grid overlay on canvas (mirrors captureFace() grid drawing in C++)
function drawGrid(canvas) {
  const ctx = canvas.getContext('2d');
  const { width, height } = canvas;
  const startX = Math.floor((width - GRID_SIZE) / 2);
  const startY = Math.floor((height - GRID_SIZE) / 2);

  ctx.strokeStyle = 'rgba(255,255,255,0.9)';
  ctx.lineWidth = 2;
  for (let i = 0; i <= 3; i++) {
    // horizontal lines
    ctx.beginPath();
    ctx.moveTo(startX, startY + i * BOX_SIZE);
    ctx.lineTo(startX + GRID_SIZE, startY + i * BOX_SIZE);
    ctx.stroke();
    // vertical lines
    ctx.beginPath();
    ctx.moveTo(startX + i * BOX_SIZE, startY);
    ctx.lineTo(startX + i * BOX_SIZE, startY + GRID_SIZE);
    ctx.stroke();
  }
}

// ---- Component ----

const CameraScanner = ({ onComplete, addLog }) => {
  const videoRef = useRef(null);
  const overlayCanvasRef = useRef(null);
  const captureCanvasRef = useRef(null);
  const streamRef = useRef(null);
  const animFrameRef = useRef(null);

  const [faceIndex, setFaceIndex] = useState(0);
  const [capturedFaces, setCapturedFaces] = useState([]); // array of 3x3 color arrays
  const [lastCapture, setLastCapture] = useState(null);   // colors for preview
  const [error, setError] = useState(null);
  const [ready, setReady] = useState(false);

  // Start webcam
  useEffect(() => {
    let stopped = false;
    navigator.mediaDevices.getUserMedia({ video: { facingMode: 'user' } })
      .then(stream => {
        if (stopped) { stream.getTracks().forEach(t => t.stop()); return; }
        streamRef.current = stream;
        if (videoRef.current) {
          videoRef.current.srcObject = stream;
          videoRef.current.onloadedmetadata = () => setReady(true);
        }
      })
      .catch(err => {
        setError(`Camera error: ${err.message}`);
        addLog(`Camera error: ${err.message}`, 'error');
      });

    return () => {
      stopped = true;
      if (streamRef.current) streamRef.current.getTracks().forEach(t => t.stop());
      if (animFrameRef.current) cancelAnimationFrame(animFrameRef.current);
    };
  }, []);

  // Draw grid overlay on top of live video each frame
  useEffect(() => {
    if (!ready) return;
    const video = videoRef.current;
    const canvas = overlayCanvasRef.current;
    if (!video || !canvas) return;

    const drawLoop = () => {
      canvas.width = video.videoWidth || canvas.offsetWidth;
      canvas.height = video.videoHeight || canvas.offsetHeight;
      const ctx = canvas.getContext('2d');
      ctx.drawImage(video, 0, 0, canvas.width, canvas.height);
      drawGrid(canvas);
      animFrameRef.current = requestAnimationFrame(drawLoop);
    };
    animFrameRef.current = requestAnimationFrame(drawLoop);
    return () => cancelAnimationFrame(animFrameRef.current);
  }, [ready]);

  const handleCapture = useCallback(() => {
    const video = videoRef.current;
    const canvas = captureCanvasRef.current;
    if (!video || !canvas) return;

    canvas.width = video.videoWidth;
    canvas.height = video.videoHeight;
    const ctx = canvas.getContext('2d');
    ctx.drawImage(video, 0, 0);

    const colors = extractFaceColors(canvas);
    setLastCapture(colors);
  }, []);

  const handleAccept = useCallback(() => {
    if (!lastCapture) return;
    const newFaces = [...capturedFaces, lastCapture];
    setCapturedFaces(newFaces);
    setLastCapture(null);

    const nextIndex = faceIndex + 1;
    if (nextIndex >= 6) {
      // All 6 faces captured — assemble cube state object
      const faceNames = FACE_ORDER;
      const cubeState = {};
      faceNames.forEach((face, i) => {
        cubeState[face] = newFaces[i];
      });
      addLog('All 6 faces scanned. Applying cube state...', 'info');
      onComplete(cubeState);
    } else {
      setFaceIndex(nextIndex);
      addLog(`Face ${FACE_ORDER[faceIndex]} captured. Now scan: ${FACE_INFO[FACE_ORDER[nextIndex]].label}`, 'info');
    }
  }, [lastCapture, capturedFaces, faceIndex, onComplete, addLog]);

  const handleRetake = () => setLastCapture(null);

  const currentFace = FACE_ORDER[faceIndex];
  const info = FACE_INFO[currentFace];

  if (error) {
    return (
      <div className="mt-4 p-3 rounded-lg bg-red-900/30 border border-red-500/30 text-red-400 text-sm">
        {error}
      </div>
    );
  }

  return (
    <div className="mt-4 space-y-3">
      {/* Face progress indicators */}
      <div className="flex gap-1">
        {FACE_ORDER.map((face, i) => (
          <div
            key={face}
            className="flex-1 h-1.5 rounded-full"
            style={{
              backgroundColor: i < capturedFaces.length
                ? FACE_INFO[face].color
                : i === faceIndex
                  ? 'rgba(255,255,255,0.4)'
                  : 'rgba(255,255,255,0.1)'
            }}
            title={FACE_INFO[face].label}
          />
        ))}
      </div>

      {/* Instruction */}
      <div className="text-sm font-medium text-slate-300 flex items-center gap-2">
        <span
          className="inline-block w-3 h-3 rounded-full border border-slate-600"
          style={{ backgroundColor: info.color }}
        />
        <span>Face {faceIndex + 1}/6 — {info.label}: {info.instruction}</span>
      </div>

      {/* Video + overlay */}
      <div className="relative rounded-xl overflow-hidden bg-black" style={{ maxWidth: 480, margin: '0 auto' }}>
        <video
          ref={videoRef}
          autoPlay
          playsInline
          muted
          className="w-full block"
          style={{ visibility: lastCapture ? 'hidden' : 'visible' }}
        />
        <canvas
          ref={overlayCanvasRef}
          className="absolute inset-0 w-full h-full"
          style={{ display: lastCapture ? 'none' : 'block' }}
        />
        {/* Hidden capture canvas */}
        <canvas ref={captureCanvasRef} className="hidden" />
      </div>

      {/* Captured face preview */}
      {lastCapture && (
        <div className="flex flex-col items-center gap-3">
          <p className="text-sm text-slate-400">Detected colors — does this look right?</p>
          <div
            className="grid gap-0.5 rounded overflow-hidden border border-slate-600"
            style={{ gridTemplateColumns: 'repeat(3, 48px)', gridTemplateRows: 'repeat(3, 48px)' }}
          >
            {lastCapture.flat().map((color, i) => (
              <div
                key={i}
                className="w-12 h-12"
                style={{ backgroundColor: COLOR_DISPLAY[color] || '#555' }}
                title={color}
              />
            ))}
          </div>
          <div className="flex gap-3">
            <button
              onClick={handleRetake}
              className="px-4 py-2 text-sm rounded-lg bg-slate-700 hover:bg-slate-600 text-slate-200 transition-colors"
            >
              Retake
            </button>
            <button
              onClick={handleAccept}
              className="px-4 py-2 text-sm rounded-lg bg-indigo-600 hover:bg-indigo-500 text-white font-medium transition-colors"
            >
              Accept &amp; Next
            </button>
          </div>
        </div>
      )}

      {/* Capture button */}
      {!lastCapture && ready && (
        <div className="flex justify-center">
          <button
            onClick={handleCapture}
            className="px-6 py-2.5 text-sm font-medium rounded-lg bg-indigo-600 hover:bg-indigo-500 text-white transition-colors shadow-md"
          >
            Capture Face
          </button>
        </div>
      )}

      {!ready && !error && (
        <p className="text-center text-sm text-slate-500 animate-pulse">Initializing camera...</p>
      )}
    </div>
  );
};

export default CameraScanner;
