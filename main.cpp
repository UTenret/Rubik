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

string colorize(char color) {
    switch (color) {
        case 'W': return "\033[97mW\033[0m"; // White
        case 'Y': return "\033[93mY\033[0m"; // Yellow
        case 'R': return "\033[91mR\033[0m"; // Red
        case 'O': return "\033[95mO\033[0m"; // Orange
        case 'G': return "\033[92mG\033[0m"; // Green
        case 'B': return "\033[94mB\033[0m"; // Blue
        default: return string(1, color);
    }
}

void printCube(char* cube) {
    cout << "|||PRINTING CUBE|||" << endl;
    cout << endl;
    
    // Print U
	cout << "    ";
    for (int i = 36; i < 45; i++) {
        cout << colorize(cube[i]);
        if ((i + 1) % 3 == 0) cout << endl << "    ";
    }
    cout << endl;

    // Print LFR
    for (int row = 0; row < 3; row++) {
        // Print L
        for (int i = 27 + row * 3; i < 30 + row * 3; i++) {
            cout << colorize(cube[i]);
        }
        cout << " ";
        // Print F
        for (int i = 0 + row * 3; i < 3 + row * 3; i++) {
            cout << colorize(cube[i]);
        }
        cout << " ";
        // Print R
        for (int i = 9 + row * 3; i < 12 + row * 3; i++) {
            cout << colorize(cube[i]);
        }
        cout << endl;
    }
    cout << endl;

    // Print D
	cout << "    ";
    for (int i = 45; i < 54; i++) {
        cout << colorize(cube[i]);
        if ((i + 1) % 3 == 0) cout << endl << "    ";
    }
    cout << endl;

    // Print B
	cout << "    ";
	for (int i = 18; i < 27; i++) {
        cout << colorize(cube[i]);
        if ((i + 1) % 3 == 0) cout << endl << "    ";
    }
}

/*
 U
LFR
 D
 B
*/

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

void moveD(char* cube) {
	char tempFront[3] = {cube[6], cube[7], cube[8]};
	char tempRight[3] = {cube[15], cube[16], cube[17]};
	char tempBack[3] = {cube[24], cube[25], cube[26]};
	char tempLeft[3] = {cube[33], cube[34], cube[35]};

	char tempDown[9] = {cube[51], cube[48], cube[45],
						cube[52], cube[49], cube[46],
						cube[53], cube[50], cube[47]};
	for (int i = 0; i < 9; i++) {
		cube[i + 45] = tempDown[i];
	}
	for (int i = 0; i < 3; i++) {
		cube[i + 6] = tempLeft[i];
		cube[i + 15] = tempFront[i];
		cube[i + 24] = tempRight[i];
		cube[i + 33] = tempBack[i];
	}
		
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
	cube[42] = tempLeft[2];
	cube[43] = tempLeft[1];
	cube[44] = tempLeft[0];
	cube[45] = tempRight[2];
	cube[46] = tempRight[1];
	cube[47] = tempRight[0];
}

void moveU(char* cube) {
	char tempFront[3] = {cube[0], cube[1], cube[2]};
	char tempRight[3] = {cube[9], cube[10], cube[11]};
	char tempBack[3] = {cube[18], cube[19], cube[20]};
	char tempLeft[3] = {cube[27], cube[28], cube[29]};

	char tempU[9] = {cube[42],cube[39],cube[36],
					cube[43],cube[40],cube[37],
					cube[44],cube[41],cube[38]};
	for (int i = 0; i < 9; i++) {
		cube[i + 36] = tempU[i];						//ROTATE THE UP
	}
	for (int i = 0; i < 3; i++) {						// rotate the top row
		cube[i] = tempRight[i];
		cube[i + 9] = tempBack[i];
		cube[i + 18] = tempLeft[i];
		cube[i + 27] = tempFront[i];
	}

}

void moveR(char* cube) {
	char tempFront[3] = {cube[2],cube[5],cube[8]};
	char tempUp[3] = {cube[44],cube[41],cube[38]};
	char tempDown[3] = {cube[47],cube[50],cube[53]};
	char tempBack[3] = {cube[24],cube[21],cube[18]};

	char tempRight[9] = {cube[15], cube[12], cube[9],
						cube[16], cube[13], cube[10],
						cube[17], cube[14], cube[11]};

	for (int i = 0; i < 9; i++) {
		cube[i + 9] = tempRight[i];
	}
	for (int i = 0, j = 0; i < 9; i += 3, j++) {
		cube[i + 2] = tempDown[j];
		cube[i + 18] = tempUp[j];
		cube[i + 38] = tempFront[j];
		cube[i + 47] = tempBack[j];
	}
}

void moveRPrime(char *cube) {
	moveR(cube);
	moveR(cube);
	moveR(cube);
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

void moveDPrime(char* cube) {
	moveD(cube);
	moveD(cube);
	moveD(cube);
}

void applyInverseMove(char* cube, const string& moveStr) {
    if (moveStr == "U") moveUPrime(cube);
    else if (moveStr == "U'") moveU(cube);
    else if (moveStr == "F") moveFPrime(cube);
    else if (moveStr == "F'") moveF(cube);
    else if (moveStr == "R") moveRPrime(cube);
    else if (moveStr == "R'") moveR(cube);
    else if (moveStr == "D") moveDPrime(cube);
    else if (moveStr == "D'") moveD(cube);
}

bool areInverseMoves(const std::string& move1, const std::string& move2) {
    if (move1.front() == move2.front()) {
        if ((move1.back() == '\'' && move2.back() != '\'') || 
            (move1.back() != '\'' && move2.back() == '\'')) {
            return true;
        }
    }
    return false;
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
		{moveR, "R"},
		{moveRPrime, "R'"},
		{moveD, "D"},
		{moveDPrime, "D'"},
	};
	for (auto& [moveFunc, moveStr] : moves) {
		 if (!solution.empty() && areInverseMoves(solution.back(), moveStr)) {
            continue;
        }
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

vector<string> splitString(const string& str, char delimiter = ' ') {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

void applyMove(char* cube, const string& moveStr) {
    if (moveStr == "U") moveU(cube);
    else if (moveStr == "U'") moveUPrime(cube);
    else if (moveStr == "F") moveF(cube);
    else if (moveStr == "F'") moveFPrime(cube);
    else if (moveStr == "R") moveR(cube);
    else if (moveStr == "R'") moveRPrime(cube);
    else if (moveStr == "D") moveD(cube);
    else if (moveStr == "D'") moveDPrime(cube);
}

int main(int argc, char* av[]) {
    char cube[54] = {
        'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', // 0,  1,  2,  3   4,  5,  6,  7,  8		FRONT
        'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', // 9,  10, 11, 12, 13, 14, 15, 16, 17		RIGHT
        'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', // 18, 19, 20, 21, 22, 23, 24, 25, 26		BACK
        'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', // 27, 28, 29, 30, 31, 32, 33, 34, 35		LEFT
        'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', // 36, 37, 38, 39, 40, 41, 42, 43, 44		UP
        'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'	//  45, 46, 47, 48, 49, 50, 51, 52, 53		DOWN
    };
	
	if (argc > 1) {
		string scramble = av[1];
        vector<string> moves = splitString(scramble);
		for (const string& move : moves) {
			// printCube(cube);
			// cout << "applied move" << endl;
            applyMove(cube, move);
        }
	}
	// printCube(cube);
	// moveU(cube);
	// cube[18] = 'S';
	printCube(cube);
	std::vector <string> solution;
	for (int i = 1; i < MAX_DEPTH; i++) {
		if (dfs(cube, 0, i, solution))
			break;
	}
	// printCube(cube);
    return 0;
}
