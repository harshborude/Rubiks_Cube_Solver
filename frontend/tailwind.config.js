/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./src/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {
      colors: {
        cube: {
          white: '#ffffff',
          red: '#dc2626',
          blue: '#2563eb',
          orange: '#ea580c',
          green: '#16a34a',
          yellow: '#facc15'
        }
      }
    },
  },
  plugins: [],
}
