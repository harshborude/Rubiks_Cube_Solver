cmake_minimum_required(VERSION 3.20)

project(rubiks_cube_solver CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)

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

target_include_directories(rubiks_cube_solver PUBLIC
    "${CMAKE_SOURCE_DIR}"
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(rubiks_cube_solver PRIVATE
    ${OpenCV_LIBS}
)