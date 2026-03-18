# Stage 1: Build the React frontend
FROM node:18 AS frontend-build
WORKDIR /app/frontend
COPY frontend/package*.json ./
RUN npm install
COPY frontend/ ./
RUN npm run build

# Stage 2: Build the C++ solver
FROM ubuntu:22.04 AS cpp-build
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y build-essential cmake ninja-build git libssl-dev libasio-dev && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY Model ./Model
COPY PatternDatabases ./PatternDatabases
COPY Scanner ./Scanner
COPY Solver ./Solver
COPY main.cpp ./
# We can just build with g++ since it's a single executable now, no need for CMake
RUN g++ -std=c++17 -O2 -o rubiks_cube_solver main.cpp Model/RubiksCube.cpp Model/RubiksCube3dArray.cpp Model/RubiksCube1dArray.cpp PatternDatabases/NibbleArray.cpp PatternDatabases/PatternDatabase.cpp PatternDatabases/CornerPatternDatabase.cpp PatternDatabases/CornerDBMaker.cpp PatternDatabases/math.cpp -I .

# Stage 3: Production Node.js server
FROM node:18-slim
WORKDIR /app

# Install required runtime libs for C++ executable (libstdc++6, etc)
RUN apt-get update && apt-get install -y libstdc++6 libc6 && rm -rf /var/lib/apt/lists/*

# Copy backend
WORKDIR /app/backend
COPY backend/package*.json ./
RUN npm install --production
COPY backend/server.js ./

# Copy C++ executable and Databases
WORKDIR /app
COPY --from=cpp-build /app/rubiks_cube_solver ./
COPY Databases ./Databases

# Copy built React files
COPY --from=frontend-build /app/frontend/dist ./frontend/dist

# Expose backend port
EXPOSE 3001

# Start the Node.js backend
WORKDIR /app/backend
CMD ["node", "server.js"]
