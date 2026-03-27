#include <bits/stdc++.h>
#include <climits>
#include "../Model/RubiksCube.h"
#include "../PatternDatabases/CornerPatternDatabase.h"

#ifndef RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H
#define RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H

// True IDA* (Iterative Deepening A*) using recursive DFS with a cost bound.
//
// Key differences from the old priority-queue (A*) version:
//   - O(depth) memory instead of O(nodes): no more OOM for deep states
//   - Same-face + opposite-face pruning cuts the search tree by ~5-6x
//   - Path is tracked directly; moves are undone in-place on backtrack
//   - Supports a pre-loaded DB to avoid the ~180ms file read in server mode
//
// MOVE face groups  (move_index / 3 == face_id):
//   0=L  1=R  2=U  3=D  4=F  5=B
// Opposite pairs share the same (face/2) value: (L,R)->0, (U,D)->1, (F,B)->2
// Canonical pruning: if last face was the higher of a pair (R,D,B), skip the
// lower (L,U,F) — these moves commute so the reversed order is a duplicate.

template<typename T, typename H>
class IDAstarSolver {
private:
    std::unique_ptr<CornerPatternDatabase> ownedDB; // non-null when loading from file
    CornerPatternDatabase* dbPtr;                   // always points to the active DB

    std::vector<RubiksCube::MOVE> path;

    // Recursive DFS step.
    //   cube     — current state, modified in-place and undone on backtrack
    //   g        — cost so far (number of moves applied)
    //   bound    — current IDA* cost bound
    //   lastFace — face index of the last applied move (-1 = none)
    //   nextBnd  — updated to the minimum f-cost that exceeded bound
    // Returns true when a solution is found; path contains the move sequence.
    bool dfs(T& cube, int g, int bound, int lastFace, int& nextBnd) {
        int h = dbPtr->getNumMoves(cube);
        int f = g + h;
        if (f > bound) {
            if (f < nextBnd) nextBnd = f;
            return false;
        }
        if (cube.isSolved()) return true;

        for (int i = 0; i < 18; i++) {
            int face = i / 3;

            // Prune 1: don't move the same face twice in a row
            if (face == lastFace) continue;

            // Prune 2: canonical ordering for opposite-face pairs.
            // If last face was the higher of a pair (R=1, D=3, B=5), skip
            // the lower (L=0, U=2, F=4) to avoid enumerating both R→L and L→R.
            if (lastFace != -1 && (lastFace / 2 == face / 2) && (lastFace > face)) continue;

            auto mv = RubiksCube::MOVE(i);
            cube.move(mv);
            path.push_back(mv);

            if (dfs(cube, g + 1, bound, face, nextBnd)) return true;

            path.pop_back();
            cube.invert(mv);
        }
        return false;
    }

public:
    T rubiksCube;

    // Constructor 1: load the pattern database from file (CLI / one-shot mode)
    IDAstarSolver(T _rubiksCube, const std::string& fileName)
        : rubiksCube(_rubiksCube),
          ownedDB(std::make_unique<CornerPatternDatabase>()),
          dbPtr(nullptr) {
        ownedDB->fromFile(fileName);
        dbPtr = ownedDB.get();
    }

    // Constructor 2: use a pre-loaded database (server mode — no file I/O per request)
    IDAstarSolver(T _rubiksCube, CornerPatternDatabase& preloadedDB)
        : rubiksCube(_rubiksCube),
          ownedDB(nullptr),
          dbPtr(&preloadedDB) {}

    std::vector<RubiksCube::MOVE> solve() {
        int bound = dbPtr->getNumMoves(rubiksCube);
        path.clear();

        while (true) {
            int nextBnd = INT_MAX;
            T cube = rubiksCube; // work on a copy; rubiksCube is untouched until solved
            if (dfs(cube, 0, bound, -1, nextBnd)) {
                rubiksCube = cube;
                return path;
            }
            if (nextBnd == INT_MAX) return {}; // cube is unsolvable
            bound = nextBnd;
            path.clear();
        }
    }
};

#endif // RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H
