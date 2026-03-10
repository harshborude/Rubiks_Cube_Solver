#include <iostream>
#include "Model/RubiksCube1dArray.cpp"
#include "Model/RubiksCube3dArray.cpp"
using namespace std;

int main(){
    string input = "WBBYWWYYYBRRBGWGOOGBBORRWGYRBYGBYOGWOOROORORRGYGGYWWWB";
    RubiksCube1dArray cube;
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
                }
                cube.setColor(static_cast<RubiksCube::FACE>(face), i, j, color);
            }
        }
    }
    
    // Copy the exact edge Orientation logic from validateSolvability here
    using FACE = RubiksCube::FACE;
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
    auto edgeOrientation = [](char c1, FACE f1, char c2, FACE f2) -> int {
        bool c1_is_ud = (c1 == 'W' || c1 == 'Y');
        bool c2_is_ud = (c2 == 'W' || c2 == 'Y');
        bool f1_is_ud = (f1 == FACE::UP || f1 == FACE::DOWN);
        bool f2_is_ud = (f2 == FACE::UP || f2 == FACE::DOWN);

        if (c1_is_ud || c2_is_ud) {
            if (c1_is_ud && f1_is_ud) return 0;
            if (c2_is_ud && f2_is_ud) return 0;
            return 1;
        }
        bool c1_is_fb = (c1 == 'R' || c1 == 'O');
        bool c2_is_fb = (c2 == 'R' || c2 == 'O');
        bool f1_is_fb = (f1 == FACE::FRONT || f1 == FACE::BACK);
        bool f2_is_fb = (f2 == FACE::FRONT || f2 == FACE::BACK);
        if (c1_is_fb && f1_is_fb) return 0;
        if (c2_is_fb && f2_is_fb) return 0;
        return 1;
    };

    int sum = 0;
    for(int i=0; i<12; i++) {
        char c1 = RubiksCube::getColorLetter(cube.getColor(edges[i].f1, edges[i].r1, edges[i].c1));
        char c2 = RubiksCube::getColorLetter(cube.getColor(edges[i].f2, edges[i].r2, edges[i].c2));
        int orient = edgeOrientation(c1, edges[i].f1, c2, edges[i].f2);
        cout << "Edge " << i << " (" << c1 << c2 << ") orient: " << orient << "\n";
        sum += orient;
    }
    cout << "Total edge sum = " << sum << ", % 2 = " << (sum % 2) << "\n";
    return 0;
}
