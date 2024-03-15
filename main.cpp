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

#define MAX_DEPTH 12

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

bool isSolved(char* cube) {
	for (int i = 0; i < 9; i++) {
		if (cube[i] != 'B')
			return false;
	}
	for (int i = 9; i < 18; i++) {
		if (cube[i] != 'R')
			return false;
	}
	for (int i = 18; i < 27; i++) {
		if (cube[i] != 'G')
			return false;
	}
	for (int i = 27; i < 36; i++) {
		if (cube[i] != 'O')
			return false;
	}
	for (int i = 36; i < 45; i++) {
		if (cube[i] != 'Y')
			return false;
	}
	for (int i = 45; i < 54; i++) {
		if (cube[i] != 'W')
			return false;
	}
	return true;
}

void moveF(char* cube) {
	char tempLeft[3] = {cube[29], cube[32], cube[35]};
	char tempRight[3] = {cube[9], cube[12], cube[15]};
	char tempUp[3] = {cube[42], cube[43], cube[44]};
	char tempDown[3] = {cube[45], cube[46], cube[47]};

	char tempFront[9] = {cube[6], cube[3], cube[0],
						cube[7], cube[4], cube[1],
						cube[8], cube[5], cube[2]};
	for (int i = 0; i < 9; i++) {
		cube[i] = tempFront[i];
	}
	for (int i = 0, j = 0; i < 9; i += 3, j++) {
		cube[i + 9] = tempUp[j];
		cube[i + 29] = tempDown[j];
	}
	for (int i = 0; i < 3; i++) {
		cube[i + 42] = tempLeft[i];
		cube[i + 45] = tempRight[i];
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
	for (int i = 0; i < 3; i++) {						// rotate the top row
		cube[i] = tempRight[i];
		cube[i + 9] = tempBack[i];
		cube[i + 18] = tempLeft[i];
		cube[i + 27] = tempFront[i];
	}

}

void moveUPrime(char* cube) {
	moveU(cube);
	moveU(cube);
	moveU(cube);
}

void moveFPrime(char *cube) {
	moveF(cube);
	moveF(cube);
	moveF(cube);
}

void applyInverseMove(char* cube, const string& moveStr) {
    if (moveStr == "U") moveUPrime(cube);
    else if (moveStr == "U'") moveU(cube);
    else if (moveStr == "F") moveFPrime(cube);
    else if (moveStr == "F'") moveF(cube);
}

bool dfs(char* cube, int depth, int maxDepth, vector<string>& solution) {
	if(isSolved(cube)) {
		printCube(cube);
		cout << "SOLUTION :";
		for (const auto& move : solution) {
			cout << move << " ";
		}
		cout << endl;
		return true;
	}
	if(depth == maxDepth)
		return false;

	std::vector <pair<void(*)(char*), string>> moves {
		{moveU, "U"},
		{moveUPrime, "U'"},
		{moveF, "F"},
		{moveFPrime, "F'"},
	};
	for (auto& [moveFunc, moveStr] : moves) {
		moveFunc(cube);
		solution.push_back(moveStr);
		if (dfs(cube, depth + 1, maxDepth, solution)) {
			return true;
		}
		applyInverseMove(cube, moveStr); 
		solution.pop_back();
	}
	return false;
}

int main(int argc, string* av[]) {
    char cube[54] = {
        'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', // 0,  1,  2,  3   4,  5,  6,  7,  8		FRONT
        'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', // 9,  10, 11, 12, 13, 14, 15, 16, 17		RIGHT
        'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', // 18, 19, 20, 21, 22, 23, 24, 25, 26		BACK
        'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', // 27, 28, 29, 30, 31, 32, 33, 34, 35		LEFT
        'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', // 36, 37, 38, 39, 40, 41, 42, 43, 44		UP
        'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'	//  45, 46, 47, 48, 49, 50, 51, 52, 53		DOWN
    };
	
	// printCube(cube);
	// moveU(cube);
	// printCube(cube);
	std::vector <string> solution;
	moveF(cube);
	moveU(cube);
	moveU(cube);
	for (int i = 1; i < MAX_DEPTH; i++) {
		if (dfs(cube, 0, i, solution))
			break;
	}
	printCube(cube);
    return 0;
}