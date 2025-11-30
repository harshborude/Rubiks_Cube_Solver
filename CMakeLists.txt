# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Set the project name and language
project(rubiks_cube_solver CXX)

# Set the C++ standard (17 is a good modern choice)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the OpenCV package
find_package(OpenCV REQUIRED)

# --- Define Your Executable ---

# Add the executable and list ALL .cpp source files
# (NO .h files!)
add_executable(rubiks_cube_solver
    main.cpp
    Model/RubiksCube.cpp
    Model/RubiksCube3dArray.cpp
    Model/RubiksCube1dArray.cpp
    Model/RubiksCubeBitboard.cpp
    PatternDatabases/NibbleArray.cpp
    PatternDatabases/PatternDatabase.cpp
    PatternDatabases/CornerPatternDatabase.cpp
    PatternDatabases/CornerDBMaker.cpp
    PatternDatabases/math.cpp
    Scanner/CubeScanner.cpp
)

# --- Configure Target-Specific Properties ---

# Tell your target where to find all its header files
# This is the modern replacement for include_directories()
target_include_directories(rubiks_cube_solver PUBLIC
    "${CMAKE_SOURCE_DIR}"    # Lets you do #include "Model/RubiksCube.h"
    ${OpenCV_INCLUDE_DIRS}  # Adds all OpenCV headers
)

# Link your target against all the libraries it needs
target_link_libraries(rubiks_cube_solver PRIVATE
    ${OpenCV_LIBS}
)