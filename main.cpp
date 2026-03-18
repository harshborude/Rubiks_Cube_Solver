
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
//     RubiksCube1dArray cube;
//     scanner.scan(cube);
//     cube.print();

//     IDAstarSolver<RubiksCube1dArray, Hash1d> idAstarSolver(cube, fileName);
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
#include "Model/RubiksCube1dArray.cpp"

using namespace std;

void manualInput(RubiksCube1dArray &cube);
void solveCube(RubiksCube1dArray &cube, const string &fileName);
bool validateCubeColors(RubiksCube1dArray &cube);
string validateSolvability(RubiksCube1dArray &cube);

int main(int argc, char* argv[]) {
    try {

    string fileName = "Databases/cornerDepth5V1.txt";
    RubiksCube1dArray cube;

        // If an argument is provided (e.g. from Node backend), parse it and run non-interactively
        if (argc >= 2) {
            string mode = argv[1];

            // SCRAMBLE MODE: rubiks_cube_solver.exe scramble <depth>
            if (mode == "scramble" && argc == 3) {
                int depth = stoi(argv[2]);
                auto shuffleMoves = cube.randomShuffleCube(depth);

                // Output the scramble moves
                cout << "MOVES:";
                for (auto m : shuffleMoves) {
                    cout << cube.getMove(m) << " ";
                }
                cout << endl;

                // Output the cube state as a 54-char string
                cout << "STATE:";
                for (int face = 0; face < 6; face++) {
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            auto color = cube.getColor(static_cast<RubiksCube::FACE>(face), i, j);
                            cout << RubiksCube::getColorLetter(color);
                        }
                    }
                }
                cout << endl;
                return 0;
            }

            // SOLVE MODE: rubiks_cube_solver.exe <54-char-state>
            string input = mode;
            if (input.length() != 54) {
                cout << "Error: Expected 54 characters." << endl;
                return 1;
            }

            for (int face = 0; face < 6; face++) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        char c = input[face * 9 + i * 3 + j];
                        RubiksCube::COLOR color;
                        switch (c) {
                            case 'W': color = RubiksCube::COLOR::WHITE; break;
                            case 'R': color = RubiksCube::COLOR::RED; break;
                            case 'O': color = RubiksCube::COLOR::ORANGE; break;
                            case 'Y': color = RubiksCube::COLOR::YELLOW; break;
                            case 'G': color = RubiksCube::COLOR::GREEN; break;
                            case 'B': color = RubiksCube::COLOR::BLUE; break;
                            default: return 1; // Error
                        }
                        cube.setColor(static_cast<RubiksCube::FACE>(face), i, j, color);
                    }
                }
            }

            if (!validateCubeColors(cube)) {
                cout << "Error: Invalid colors." << endl;
                return 1;
            }

            string solvabilityError = validateSolvability(cube);
            if (!solvabilityError.empty()) {
                cout << "Error: " << solvabilityError << endl;
                return 1;
            }

            int algo_choice = 1; // Default to IDA*
            if (argc >= 3) {
                algo_choice = stoi(argv[2]);
            }

            vector<RubiksCube::MOVE> solve_moves;
            if (algo_choice == 1) {
                IDAstarSolver<RubiksCube1dArray, Hash1d> solver(cube, fileName);
                solve_moves = solver.solve();
            } else if (algo_choice == 2) {
                BFSSolver<RubiksCube1dArray, Hash1d> solver(cube);
                solve_moves = solver.solve();
            } else if (algo_choice == 3) {
                DFSSolver<RubiksCube1dArray, Hash1d> solver(cube, 8);
                solve_moves = solver.solve();
            } else if (algo_choice == 4) {
                IDDFSSolver<RubiksCube1dArray, Hash1d> solver(cube, 8);
                solve_moves = solver.solve();
            }
            
            // PRINT ONLY THE SOLUTION MOVES FOR THE BACKEND TO READ
            for (auto move : solve_moves) {
                cout << cube.getMove(move) << " ";
            }
            cout << endl;
            return 0;
        }

     cout << "Choose mode:\n";
cout << "1 - Manual Input\n";
cout << "2 - Random Shuffle\n";
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

void manualInput(RubiksCube1dArray &cube) {
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

void solveCube(RubiksCube1dArray &cube, const string &fileName) {
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
        IDAstarSolver<RubiksCube1dArray, Hash1d> solver(cube, fileName);
        solve_moves = solver.solve();
        solver.rubiksCube.print();
    } else if (algo_choice == 2) {
        cout << "Solving with BFS...\n";
        BFSSolver<RubiksCube1dArray, Hash1d> solver(cube);
        solve_moves = solver.solve();
        solver.rubiksCube.print();
    } else if (algo_choice == 3) {
        int depth;
        cout << "Enter max depth for DFS: ";
        cin >> depth;
        cout << "Solving with DFS...\n";
        DFSSolver<RubiksCube1dArray, Hash1d> solver(cube, depth);
        solve_moves = solver.solve();
        solver.rubiksCube.print();
    } else if (algo_choice == 4) {
        int depth;
        cout << "Enter max depth for IDDFS: ";
        cin >> depth;
        cout << "Solving with IDDFS...\n";
        IDDFSSolver<RubiksCube1dArray, Hash1d> solver(cube, depth);
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

// ==================== SOLVABILITY VALIDATION ====================
// Checks the three mathematical invariants of a valid Rubik's Cube:
// 1. Corner orientation sum % 3 == 0
// 2. Edge orientation sum % 2 == 0  
// 3. Corner permutation parity == Edge permutation parity
// Returns empty string if valid, or an error message if invalid.

string validateSolvability(RubiksCube1dArray &cube) {
    using FACE = RubiksCube::FACE;

        // ---- CHECK 1: Corner permutation collection ----
        vector<uint8_t> cornerPerm(8);
        set<uint8_t> cornerSet;
    for (uint8_t i = 0; i < 8; i++) {
        uint8_t idx = cube.getCornerIndex(i);
        if (idx >= 8) return "Invalid corner piece detected at position " + to_string(i) + ".";
        cornerPerm[i] = idx;
        cornerSet.insert(idx);
    }
    if (cornerSet.size() != 8) return "Duplicate or missing corner pieces detected.";

    // ---- CHECK 1: Corner orientation sanity ----
    // Each corner must contain exactly one U/D color (W or Y).
    for (uint8_t i = 0; i < 8; i++) {
        string corner = cube.getCornerColorString(i);
        int udCount = 0;
        for (char c : corner) {
            if (c == 'W' || c == 'Y') udCount++;
        }
        if (udCount != 1) {
            return "Invalid corner orientation (twisted or missing U/D color).";
        }
    }
    // The sum of corner orientations modulo 3 must be 0 for a solvable cube.
    // We compute orientation using the existing helper for consistency.
        int orient_map[8][3] = {
            {0, 2, 1}, // 0: UFR
            {0, 1, 2}, // 1: UFL
            {0, 2, 1}, // 2: UBL
            {0, 1, 2}, // 3: UBR
            {0, 1, 2}, // 4: DFR
            {0, 2, 1}, // 5: DFL
            {0, 2, 1}, // 6: DBR
            {0, 1, 2}  // 7: DBL
        };

        int cornerOrientSum = 0;
        for (uint8_t i = 0; i < 8; i++) {
            string corner = cube.getCornerColorString(i);
            int udIdx = -1;
            for (int j = 0; j < 3; j++) {
                if (corner[j] == 'W' || corner[j] == 'Y') {
                    udIdx = j;
                    break;
                }
            }
            if (udIdx == -1) {
                return "Invalid corner orientation (twisted or missing U/D color).";
            }
            cornerOrientSum += orient_map[i][udIdx];
        }
        if (cornerOrientSum % 3 != 0) {
            return "Invalid corner orientation (twist parity).";
        }

    // ---- Edge identification ----
    // 12 edges in order: UF, UR, UB, UL, DF, DR, DB, DL, FR, FL, BR, BL
    // Each edge defined by its two facelets: {face1, row1, col1, face2, row2, col2}
    struct EdgeDef {
        FACE f1; int r1, c1;
        FACE f2; int r2, c2;
    };
    EdgeDef edges[12] = {
        {FACE::UP, 2, 1, FACE::FRONT, 0, 1},    // UF
        {FACE::UP, 1, 2, FACE::RIGHT, 0, 1},    // UR
        {FACE::UP, 0, 1, FACE::BACK, 0, 1},     // UB
        {FACE::UP, 1, 0, FACE::LEFT, 0, 1},     // UL
        {FACE::DOWN, 0, 1, FACE::FRONT, 2, 1},  // DF
        {FACE::DOWN, 1, 2, FACE::RIGHT, 2, 1},  // DR
        {FACE::DOWN, 2, 1, FACE::BACK, 2, 1},   // DB
        {FACE::DOWN, 1, 0, FACE::LEFT, 2, 1},   // DL
        {FACE::FRONT, 1, 2, FACE::RIGHT, 1, 0}, // FR
        {FACE::FRONT, 1, 0, FACE::LEFT, 1, 2},  // FL
        {FACE::BACK, 1, 0, FACE::RIGHT, 1, 2},  // BR
        {FACE::BACK, 1, 2, FACE::LEFT, 1, 0},   // BL
    };

    // Map each edge color pair to a canonical edge index (0-11)
    // Solved edge colors in order: WR, WB, WO, WG, YR, YB, YO, YG, RB, RG, OB, OG
    auto edgeId = [](char c1, char c2) -> int {
        string s = "";
        s += c1; s += c2;
        // Canonical: always sort so we can match regardless of orientation
        string r = ""; r += c2; r += c1;
        // Match against known edge pairs
        vector<pair<string,string>> knownEdges = {
            {"WR", "RW"}, {"WB", "BW"}, {"WO", "OW"}, {"WG", "GW"},
            {"YR", "RY"}, {"YB", "BY"}, {"YO", "OY"}, {"YG", "GY"},
            {"RB", "BR"}, {"RG", "GR"}, {"OB", "BO"}, {"OG", "GO"},
        };
        for (int i = 0; i < 12; i++) {
            if (s == knownEdges[i].first || s == knownEdges[i].second) return i;
        }
        return -1; // Invalid edge
    };

    // Determine edge orientation:
    // Determine edge orientation:
    // Every edge piece has a primary color: W or Y if it possesses one, otherwise R or O.
    // An edge is oriented (0) if its primary color is on the f1 face (the 'primary' facelet of the slot).
    auto edgeOrientation = [](char c1, FACE f1, char c2, FACE f2) -> int {
        char primary_color;
        if (c1 == 'W' || c1 == 'Y' || c2 == 'W' || c2 == 'Y') {
            primary_color = (c1 == 'W' || c1 == 'Y') ? c1 : c2;
        } else {
            primary_color = (c1 == 'R' || c1 == 'O') ? c1 : c2;
        }
        
        // Is the primary color sitting on the f1 facelet?
        if ((primary_color == c1) /* implicit: since f1 is associated with c1 */) {
            return 0; // Oriented
        }
        return 1; // Flipped
    };

    vector<uint8_t> edgePerm(12);
    set<int> edgeSet;
    int edgeOrientSum = 0;

    for (int i = 0; i < 12; i++) {
        char c1 = RubiksCube::getColorLetter(cube.getColor(edges[i].f1, edges[i].r1, edges[i].c1));
        char c2 = RubiksCube::getColorLetter(cube.getColor(edges[i].f2, edges[i].r2, edges[i].c2));
        int id = edgeId(c1, c2);
        if (id == -1) return "Invalid edge piece at position " + to_string(i) + " (colors: " + string(1,c1) + string(1,c2) + ").";
        edgePerm[i] = id;
        edgeSet.insert(id);
        edgeOrientSum += edgeOrientation(c1, edges[i].f1, c2, edges[i].f2);
    }

    // ---- CHECK 2: Edge uniqueness and orientation ----
    if (edgeSet.size() != 12) return "Duplicate or missing edge pieces detected.";
    if (edgeOrientSum % 2 != 0) return "Invalid edge orientation (flipped edge in place).";

    // ---- CHECK 3: Permutation parity ----
    // The getCornerIndex() and edgeId() return encoded IDs, not natural slot positions.
    // On a solved cube, the mapping slot→id might not be identity.
    // To check parity, we compute the solved baseline first, then compare.
    
    // Build solved cube to get baseline permutations
    RubiksCube1dArray solvedCube;
    vector<uint8_t> solvedCornerPerm(8);
    for (uint8_t i = 0; i < 8; i++) {
        solvedCornerPerm[i] = solvedCube.getCornerIndex(i);
    }

    // For edges, get solved edge baseline
    vector<uint8_t> solvedEdgePerm(12);
    for (int i = 0; i < 12; i++) {
        char c1 = RubiksCube::getColorLetter(solvedCube.getColor(edges[i].f1, edges[i].r1, edges[i].c1));
        char c2 = RubiksCube::getColorLetter(solvedCube.getColor(edges[i].f2, edges[i].r2, edges[i].c2));
        solvedEdgePerm[i] = edgeId(c1, c2);
    }

    // Compute relative permutation: relPerm[i] = where did the piece that 
    // was in slot i (in solved state) end up in the current state?
    // This is effectively: current_perm ∘ inverse(solved_perm)
    auto computeRelativeParity = [](const vector<uint8_t>& currentPerm, const vector<uint8_t>& solvedPerm) -> int {
        int n = currentPerm.size();
        // Build inverse of solved permutation: solvedInv[id] = slot
        vector<int> solvedInv(n, -1);
        for (int i = 0; i < n; i++) {
            solvedInv[solvedPerm[i]] = i;
        }
        // Build relative permutation
        vector<int> relPerm(n);
        for (int i = 0; i < n; i++) {
            relPerm[i] = solvedInv[currentPerm[i]];
        }
        // Count cycles in relative permutation
        vector<bool> visited(n, false);
        int cycles = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                cycles++;
                int j = i;
                while (!visited[j]) {
                    visited[j] = true;
                    j = relPerm[j];
                }
            }
        }
        // Parity = (n - cycles) % 2
        return (n - cycles) % 2;
    };

    int cornerParity = computeRelativeParity(cornerPerm, solvedCornerPerm);
    int edgeParity = computeRelativeParity(edgePerm, solvedEdgePerm);
    if (cornerParity != edgeParity) return "Invalid permutation parity (impossible piece swap).";

    return ""; // Valid!
}

bool validateCubeColors(RubiksCube1dArray &cube) {
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