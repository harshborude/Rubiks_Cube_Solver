#include <bits/stdc++.h>
#include "Model/RubiksCubeBitboard.cpp"

using namespace std;

int main() {
    // Create a cube and shuffle with R
    RubiksCubeBitboard cube1;
    cube1.r();

    cout << "=== Cube after R move ===" << endl;
    cube1.print();

    // Read corner orientations from the moved cube
    cout << "Corner orientations from moved cube:" << endl;
    int sum1 = 0;
    for (int i = 0; i < 8; i++) {
        uint8_t orient = cube1.getCornerOrientation(i);
        cout << "  Corner " << i << ": orient=" << (int)orient 
             << " idx=" << (int)cube1.getCornerIndex(i) 
             << " colors=" << cube1.getCornerColorString(i) << endl;
        sum1 += orient;
    }
    cout << "Sum: " << sum1 << " (mod3: " << sum1%3 << ")" << endl;

    // Now create a second cube, set its colors from the first
    RubiksCubeBitboard cube2;
    for (int face = 0; face < 6; face++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                auto color = cube1.getColor(static_cast<RubiksCube::FACE>(face), i, j);
                cube2.setColor(static_cast<RubiksCube::FACE>(face), i, j, color);
            }
        }
    }

    cout << "\n=== Cube2 after setColor ===" << endl;
    cube2.print();

    cout << "Corner orientations from setColor cube:" << endl;
    int sum2 = 0;
    for (int i = 0; i < 8; i++) {
        uint8_t orient = cube2.getCornerOrientation(i);
        cout << "  Corner " << i << ": orient=" << (int)orient 
             << " idx=" << (int)cube2.getCornerIndex(i) 
             << " colors=" << cube2.getCornerColorString(i) << endl;
        sum2 += orient;
    }
    cout << "Sum: " << sum2 << " (mod3: " << sum2%3 << ")" << endl;

    return 0;
}
