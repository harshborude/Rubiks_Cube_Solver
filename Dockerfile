# Start with an Ubuntu image to compile and run C++
FROM ubuntu:22.04

# Avoid tzdata interactive prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies (CMake, GCC, Ninja, OpenSSL, ASIO)
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    libssl-dev \
    libasio-dev \
    && rm -rf /var/lib/apt/lists/*

# Set up working directory
WORKDIR /app

# Copy all the C++ source files and Databases
COPY Model /app/Model
COPY PatternDatabases /app/PatternDatabases
COPY Solver /app/Solver
COPY backend /app/backend
COPY Databases /app/Databases
COPY CMakeLists_Backend.txt /app/CMakeLists.txt

# Create build directory and run CMake using the backend config
RUN mkdir build && cd build && \
    cmake -G Ninja -DCMAKE_BUILD_TYPE=Release .. && \
    cmake --build .

# The EXPOSE instruction indicates the port to listen on
EXPOSE 8080

# The startup command, giving it the relative path to the database
CMD ["/app/build/server", "/app/Databases/cornerDepth5V1.txt"]
