#include <iostream>
#include <vector>
#include <iomanip>

// MOVES U [UP]		U'
// MOVES D [DOWN]	D'
// MOVES R [RIGHT]	R'
// MOVES F [FRONT]	F'
// MOVES L [LEFT]	L'
// MOVES B [BACK]	B'

// ALSO 2F, 2B and so on

//
// char* [6]	center_cells;	//cannot move
// char* [24]	edge_cells;
// char* [24]	corner_cells;

using namespace std;

class Cell {
	public :

	int _color;
	Cell(int color) : _color(color) {}
};

void printCube(char* cube) {
	cout << "|||PRINTING CUBE|||" << endl;
	for (int i = 0; i < 54; i++) {
        std::cout << cube[i];
        if ((i + 1) % 3 == 0) 
            std::cout << std::endl;
        if ((i + 1) % 9 == 0) 
            std::cout << std::endl;
    }
}

void moveU(char* cube) {
	char tempFront[3] = {cube[0], cube[1], cube[2]};
	char tempRight[3] = {cube[9], cube[10], cube[11]};
	char tempBack[3] = {cube[18], cube[19], cube[20]};
	char tempLeft[3] = {cube[27], cube[28], cube[29]};

	char tempU[9] = {cube[51],cube[48],cube[45],
					cube[52],cube[49],cube[46],
					cube[53],cube[50],cube[47]};
	for (int i = 0; i < 9; i++) {
		cube[i + 45] = tempU[i];						//ROTATE THE UP
	}
	for (int i = 0; i < 3; i++) {
		cube[i] = tempRight[i];
		cube[i + 9] = tempBack[i];
		cube[i + 18] = tempLeft[i];
		cube[i + 27] = tempFront[i];
	}

}

int main() {
    char cube[54] = {
        'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', // 0,  1,  2,  3   4,  5,  6,  7,  8		FRONT
        'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', // 9,  10, 11, 12, 13, 14, 15, 16, 17		RIGHT
        'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', // 18, 19, 20, 21, 22, 23, 24, 25, 26		BACK
        'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', // 27, 28, 29, 30, 31, 32, 33, 34, 35		LEFT
        'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', // 36, 37, 38, 39, 40, 41, 42, 43, 44		UP
        'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'	//  45, 46, 47, 48, 49, 50, 51, 52, 53		DOWN
    };
	printCube(cube);
	moveU(cube);
	printCube(cube);
    return 0;
}