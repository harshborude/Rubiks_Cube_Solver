
// #include <bits/stdc++.h>
// //#include "Model/RubiksCube3dArray.cpp"
// //#include "Model/RubiksCube1dArray.cpp"
// //#include "Model/RubiksCubeBitboard.cpp"
// #include "Solver/DFSSolver.h"
// #include "Solver/BFSSolver.h"
// #include "Solver/IDDFSSolver.h"
// #include "Solver/IDAstarSolver.h"
// //#include "PatternDatabases/CornerPatternDatabase.h"
// #include "PatternDatabases/CornerDBMaker.h"
// #include "Scanner/CubeScanner.h"

// using namespace std;

// int main() {
// //    RubiksCube3dArray object3DArray;
// //    RubiksCube1dArray object1dArray;
// //    RubiksCubeBitboard objectBitboard;
// //
// //    object3DArray.print();
// //
// //    if (object3DArray.isSolved()) cout << "SOLVED\n\n";
// //    else cout << "NOT SOLVED\n\n";
// //
// //    if (object1dArray.isSolved()) cout << "SOLVED\n\n";
// //    else cout << "NOT SOLVED\n\n";
// //
// //    if (objectBitboard.isSolved()) cout << "SOLVED\n\n";
// //    else cout << "NOT SOLVED\n\n";
// //
// //    objectBitboard.u();
// //    object3DArray.u();
// //    object1dArray.u();
// //    objectBitboard.print();
// //    object3DArray.print();
// //    object1dArray.print();
// //
// //    objectBitboard.l();
// //    object3DArray.l();
// //    object1dArray.l();
// //    objectBitboard.print();
// //    object3DArray.print();
// //    object1dArray.print();
// //
// //    objectBitboard.f();
// //    object3DArray.f();
// //    object1dArray.f();
// //    objectBitboard.print();
// //    object3DArray.print();
// //    object1dArray.print();
// //
// //    objectBitboard.r();
// //    object3DArray.r();
// //    object1dArray.r();
// //    objectBitboard.print();
// //    object3DArray.print();
// //    object1dArray.print();
// //
// //    objectBitboard.b();
// //    object3DArray.b();
// //    object1dArray.b();
// //    objectBitboard.print();
// //    object3DArray.print();
// //    object1dArray.print();
// //
// //    objectBitboard.d();
// //    object3DArray.d();
// //    object1dArray.d();
// //    objectBitboard.print();
// //    object3DArray.print();
// //    object1dArray.print();
// //
// //    if (object3DArray.isSolved()) cout << "SOLVED\n\n";
// //    else cout << "NOT SOLVED\n\n";
// //
// //    if (object1dArray.isSolved()) cout << "SOLVED\n\n";
// //    else cout << "NOT SOLVED\n\n";
// //
// //    if (objectBitboard.isSolved()) cout << "SOLVED\n\n";
// //    else cout << "NOT SOLVED\n\n";
// //
// //    objectBitboard.dPrime();
// //    object3DArray.dPrime();
// //    object1dArray.dPrime();
// //    objectBitboard.print();
// //    object3DArray.print();
// //    object1dArray.print();
// //
// //    objectBitboard.bPrime();
// //    object3DArray.bPrime();
// //    object1dArray.bPrime();
// //    objectBitboard.print();
// //    object3DArray.print();
// //    object1dArray.print();
// //
// //    objectBitboard.rPrime();
// //    object3DArray.rPrime();
// //    object1dArray.rPrime();
// //    objectBitboard.print();
// //    object3DArray.print();
// //    object1dArray.print();
// //
// //    objectBitboard.fPrime();
// //    object3DArray.fPrime();
// //    object1dArray.fPrime();
// //    objectBitboard.print();
// //    object3DArray.print();
// //    object1dArray.print();
// //
// //    objectBitboard.lPrime();
// //    object3DArray.lPrime();
// //    object1dArray.lPrime();
// //    objectBitboard.print();
// //    object3DArray.print();
// //    object1dArray.print();
// //
// //    objectBitboard.uPrime();
// //    object3DArray.uPrime();
// //    object1dArray.uPrime();
// //    objectBitboard.print();
// //    object3DArray.print();
// //    object1dArray.print();
// //
// //    if (object3DArray.isSolved()) cout << "SOLVED\n\n";
// //    else cout << "NOT SOLVED\n\n";
// //
// //    if (object1dArray.isSolved()) cout << "SOLVED\n\n";
// //    else cout << "NOT SOLVED\n\n";
// //
// //    if (objectBitboard.isSolved()) cout << "SOLVED\n\n";
// //    else cout << "NOT SOLVED\n\n";

//     // Create two Cubes ------------------------------------------------------------------------------------------

// //    RubiksCube3dArray cube1;
// //    RubiksCube3dArray cube2;

// //    RubiksCube1dArray cube1;
// //    RubiksCube1dArray cube2;

// //    RubiksCubeBitboard cube1;
// //    RubiksCubeBitboard cube2;


// //  Equality and assignment of cubes --------------------------------------------------------------------------

// //    if(cube1 == cube2) cout << "Is equal\n";
// //    else cout << "Not Equal\n";
// //
// //    cube1.randomShuffleCube(1);
// //
// //    if(cube1 == cube2) cout << "Is equal\n";
// //    else cout << "Not Equal\n";
// //
// //    cube2 = cube1;
// //
// //    if(cube1 == cube2) cout << "Is equal\n";
// //    else cout << "Not Equal\n";


// //  Unordered_map of Cubes  ------------------------------------------------------------------------------------


// //    unordered_map<RubiksCube3dArray, bool, Hash3d> mp1;

// //    unordered_map<RubiksCube1dArray, bool, Hash1d> mp1;

// //    unordered_map<RubiksCubeBitboard, bool, HashBitboard> mp1;
// //
// //    mp1[cube1] = true;
// //    cube2.randomShuffleCube(8);
// //    if (mp1[cube1]) cout << "Cube1 is present\n";
// //    else cout << "Cube1 is not present\n";
// //
// //    if (mp1[cube2]) cout << "Cube2 is present\n";
// //    else cout << "Cube2 is not present\n";
// //

// // DFS Solver Testing __________________________________________________________________________________________
// //    RubiksCube3dArray cube;
// //    cube.print();
// //
// //    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(6);
// //    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
// //    cout << "\n";
// //    cube.print();
// //
// //    DFSSolver<RubiksCube3dArray, Hash3d> dfsSolver(cube, 8);
// //    vector<RubiksCube::MOVE> solve_moves = dfsSolver.solve();
// //
// //    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
// //    cout << "\n";
// //    dfsSolver.rubiksCube.print();


// //BFS Solver -----------------------------------------------------------------------------------------------------
// //    RubiksCubeBitboard cube;
// //    cube.print();
// //
// //    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(6);
// //    for(auto move: shuffle_moves) cout << cube.getMove(move) << " ";
// //    cout << "\n";
// //    cube.print();
// //
// //    BFSSolver<RubiksCubeBitboard, HashBitboard> bfsSolver(cube);
// //    vector<RubiksCube::MOVE> solve_moves = bfsSolver.solve();
// //
// //    for(auto move: solve_moves) cout << cube.getMove(move) << " ";
// //    cout << "\n";
// //    bfsSolver.rubiksCube.print();

// // IDDFS Solver ----------------------------------------------------------------------------------------------------
// //    RubiksCubeBitboard cube;
// //    cube.print();
// //
// //    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(7);
// //    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
// //    cout << "\n";
// //    cube.print();
// //
// //    IDDFSSolver<RubiksCubeBitboard, HashBitboard> iddfsSolver(cube, 7);
// //    vector<RubiksCube::MOVE> solve_moves = iddfsSolver.solve();
// //
// //    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
// //    cout << "\n";
// //    iddfsSolver.rubiksCube.print();

// // IDA* SOLVER ---------------------------------------------------------------------------------------------------
// //    RubiksCubeBitboard cube;
// //    cube.print();
// //
// //    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(5);
// //    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
// //    cout << "\n";
// //    cube.print();
// //
// //    IDAstarSolver<RubiksCubeBitboard, HashBitboard> idAstarSolver(cube);
// //    vector<RubiksCube::MOVE> solve_moves = idAstarSolver.solve();
// //    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
// //    cout << "\n";
// //    idAstarSolver.rubiksCube.print();

// // CornerPatternDatabase Testing ---------------------------------------------------------------------------------

// //    CornerPatternDatabase cornerDB;
// //    RubiksCubeBitboard cube;
// //    cube.print();
// //
// //    cout << (int)cornerDB.getNumMoves(cube) << "\n";
// //
// //    cornerDB.setNumMoves(cube, 5);
// //
// //    cout << (int)cornerDB.getNumMoves(cube) << "\n";
// //
// //    cube.randomShuffleCube(1);
// //    cube.print();
// //    cout << (int)cornerDB.getNumMoves(cube) << "\n";
// //
// //    cornerDB.setNumMoves(cube, 6);
// //
// //    cout << (int)cornerDB.getNumMoves(cube) << "\n";


// // CornerDBMaker Testing --------------------------------------------------------------------------

// //    string fileName = "C:\\Users\\user\\CLionProjects\\rubiks-cube-solver\\Databases\\cornerDepth5V1.txt";
// //
// //    Code to create Corner Database
// //    CornerDBMaker dbMaker(fileName, 0x99);
// //    dbMaker.bfsAndStore();
// //
// //    RubiksCubeBitboard cube;
// //    auto shuffleMoves = cube.randomShuffleCube(13);
// //    cube.print();
// //    for (auto move: shuffleMoves) cout << cube.getMove(move) << " ";
// //    cout << "\n";
// //
// //    IDAstarSolver<RubiksCubeBitboard, HashBitboard> idaStarSolver(cube, fileName);
// //    auto moves = idaStarSolver.solve();
// //
// //    idaStarSolver.rubiksCube.print();
// //    for (auto move: moves) cout << cube.getMove(move) << " ";
// //    cout << "\n";

// // CubeScanner Testing ----------------------------------------------------------------------------------



//     CubeScanner scanner(0);
//     RubiksCubeBitboard cube;
//     scanner.scan(cube);
//     cube.print();

//     IDAstarSolver<RubiksCubeBitboard, HashBitboard> idAstarSolver(cube, fileName);
//     auto solve_moves = idAstarSolver.solve();

//     for (auto move: solve_moves) cout << cube.getMove(move) << " ";
//     cout << "\n";
//     idAstarSolver.rubiksCube.print();

//     return 0;
// }

#include <bits/stdc++.h>
#include "Solver/DFSSolver.h"
#include "Solver/BFSSolver.h"
#include "Solver/IDDFSSolver.h"
#include "Solver/IDAstarSolver.h"
#include "PatternDatabases/CornerDBMaker.h"
#include "Scanner/CubeScanner.h"

using namespace std;

void manualInput(RubiksCubeBitboard &cube);
void solveCube(RubiksCubeBitboard &cube, const string &fileName);
void scanFromCamera(RubiksCubeBitboard &cube);
bool validateCubeColors(RubiksCubeBitboard &cube);

int main() {
    try {
        string fileName = R"(C:\Users\harsh\OneDrive\Desktop\Rubiks_Cube_Solver-main\Rubiks_Cube_Solver-main\Databases\cornerDepth5V1.txt)";

        RubiksCubeBitboard cube;

     cout << "Choose mode:\n";
cout << "1 - Manual Input\n";
cout << "2 - Random Shuffle\n";
cout << "3 - Scan from Camera\n";
cout << "Enter choice: ";

int choice;
cin >> choice;

if (choice == 1) {
    manualInput(cube);
}
else if (choice == 2) {
    int depth;
    cout << "Enter shuffle depth (e.g. 5): ";
    cin >> depth;

    auto scrambleMoves = cube.randomShuffleCube(depth);

    cout << "\nScramble moves:\n";
    for (auto m : scrambleMoves)
        cout << cube.getMove(m) << " ";
    cout << "\n\n";
}
else if (choice == 3) {
    scanFromCamera(cube);
}
else {
    throw runtime_error("Invalid choice.");
}

cube.print();

       if (!validateCubeColors(cube)) {
    throw runtime_error("Invalid cube state: incorrect color distribution.");
}

solveCube(cube, fileName);

    } catch (const exception& e) {
        cerr << "[CRITICAL ERROR]: " << e.what() << endl;
        return 1;
    }
    return 0;
}

void manualInput(RubiksCubeBitboard &cube) {
    cout << "Enter cube face by face.\n";
    cout << "Use letters: W B O G Y R\n\n";

    for (int face = 0; face < 6; face++) {
        cout << "Enter 9 characters for face " << face << ": ";

        string input;
        cin >> input;

        if (input.length() != 9) {
            throw runtime_error("Invalid input length! Must be 9.");
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                char c = input[i * 3 + j];

                RubiksCube::COLOR color;

                switch (c) {
                    case 'W': color = RubiksCube::COLOR::WHITE; break;
                    case 'R': color = RubiksCube::COLOR::RED; break;
                    case 'O': color = RubiksCube::COLOR::ORANGE; break;
                    case 'Y': color = RubiksCube::COLOR::YELLOW; break;
                    case 'G': color = RubiksCube::COLOR::GREEN; break;
                    case 'B': color = RubiksCube::COLOR::BLUE; break;
                    default:
                        throw runtime_error("Invalid color character.");
                }

                cube.setColor(static_cast<RubiksCube::FACE>(face), i, j, color);
            }
        }
    }
}

void solveCube(RubiksCubeBitboard &cube, const string &fileName) {
    cout << "\nChoose solver algorithm:\n";
    cout << "1 - IDA*\n";
    cout << "2 - BFS\n";
    cout << "3 - DFS\n";
    cout << "4 - IDDFS\n";
    cout << "Enter choice: ";
    int algo_choice;
    cin >> algo_choice;

    vector<RubiksCube::MOVE> solve_moves;
    auto start = chrono::high_resolution_clock::now();

    if (algo_choice == 1) {
        cout << "Solving with IDA*...\n";
        IDAstarSolver<RubiksCubeBitboard, HashBitboard> solver(cube, fileName);
        solve_moves = solver.solve();
        solver.rubiksCube.print();
    } else if (algo_choice == 2) {
        cout << "Solving with BFS...\n";
        BFSSolver<RubiksCubeBitboard, HashBitboard> solver(cube);
        solve_moves = solver.solve();
        solver.rubiksCube.print();
    } else if (algo_choice == 3) {
        int depth;
        cout << "Enter max depth for DFS: ";
        cin >> depth;
        cout << "Solving with DFS...\n";
        DFSSolver<RubiksCubeBitboard, HashBitboard> solver(cube, depth);
        solve_moves = solver.solve();
        solver.rubiksCube.print();
    } else if (algo_choice == 4) {
        int depth;
        cout << "Enter max depth for IDDFS: ";
        cin >> depth;
        cout << "Solving with IDDFS...\n";
        IDDFSSolver<RubiksCubeBitboard, HashBitboard> solver(cube, depth);
        solve_moves = solver.solve();
        solver.rubiksCube.print();
    } else {
        cout << "Invalid choice!\n";
        return;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "Solution Found:\n";
    for (auto move : solve_moves)
        cout << cube.getMove(move) << " ";
    cout << "\n\n";

    cout << "Solved in " << duration.count() << " seconds!\n";
}

void scanFromCamera(RubiksCubeBitboard &cube) {
    cout << "Initializing camera...\n";

    CubeScanner scanner(0);  // 0 = default webcam
    scanner.scan(cube);

    cout << "Scan complete.\n";
}

bool validateCubeColors(RubiksCubeBitboard &cube) {

    map<RubiksCube::COLOR, int> count;

    // Initialize all counts to 0
    count[RubiksCube::COLOR::WHITE] = 0;
    count[RubiksCube::COLOR::YELLOW] = 0;
    count[RubiksCube::COLOR::RED] = 0;
    count[RubiksCube::COLOR::ORANGE] = 0;
    count[RubiksCube::COLOR::GREEN] = 0;
    count[RubiksCube::COLOR::BLUE] = 0;

    // Count all stickers
    for (int face = 0; face < 6; face++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                auto color = cube.getColor(
                    static_cast<RubiksCube::FACE>(face), i, j
                );
                count[color]++;
            }
        }
    }

    // Check each color has exactly 9
    for (auto &p : count) {
        if (p.second != 9) {
            cout << "Color validation failed.\n";
            return false;
        }
    }

    return true;
}