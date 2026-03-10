#include <iostream>
#include "Model/RubiksCube.cpp"
#include "Model/RubiksCubeBitboard.cpp"
using namespace std;
int main(){
    RubiksCubeBitboard cube;
    cube.r(); // R move
    for(int i=0;i<8;i++){
        string corner = cube.getCornerColorString(i);
        int orient = cube.getCornerOrientation(i);
        cout << "Corner "<<i<<" string="<<corner<<" orient="<<orient<<"\n";
    }
    return 0;
}
