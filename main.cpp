#include <iostream>
#include <vector>
#include <iomanip>
#include <set>

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

#define MAX_DEPTH 9

enum EdgePositions {
    UB, UR, UF, UL,
    DR, DF, DL, DB,
    FR, FL, BR, BL,
    EDGE_COUNT
};

const int edgeIndices[EDGE_COUNT][2] = {
	{37, 19},	// UB
	{42, 10},	// UR
	{44, 1},	// UF
	{39, 28},	// UL

	{50, 16},	// DR
	{46, 7},	// DF
	{48, 34},	// DL
	{52, 25},	// DB

	{5,  12},	// FR
	{3,  32},	// FL
	{21, 14},	// BR
	{23, 30},	// BL
};

string colorize(char color) {	
    switch (color) {
        case 'W': return "\033[97mW\033[0m"; // White
        case 'Y': return "\033[93mY\033[0m"; // Yellow
        case 'R': return "\033[91mR\033[0m"; // Red
		case 'O': return "\033[38;5;208mO\033[0m"; // Orange
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
        if ((i + 1) % 3 == 0 && (i != 26)) cout << endl << "    ";
    }
	cout << endl;
}

/*
 U
LFR
 D
 B
*/

bool isFullySolved(char* cube) {
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

bool isGroup0Solved(char* cube) {
    if (!((cube[1] == 'B') &&
          (cube[3] == 'B') &&
          (cube[5] == 'B') &&
          (cube[7] == 'B') &&
          (cube[10] == 'R') &&
          (cube[12] == 'R') &&
          (cube[14] == 'R') &&
          (cube[16] == 'R') &&
          (cube[19] == 'G') &&
          (cube[21] == 'G') &&
          (cube[23] == 'G') &&
          (cube[25] == 'G') &&
          (cube[28] == 'O') &&
          (cube[30] == 'O') &&
          (cube[32] == 'O') &&
          (cube[34] == 'O') &&
          (cube[37] == 'Y') &&
          (cube[39] == 'Y') &&
          (cube[41] == 'Y') &&
          (cube[43] == 'Y') &&
          (cube[46] == 'W') &&
          (cube[48] == 'W') &&
          (cube[50] == 'W') &&
          (cube[52] == 'W'))) { 
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

void moveL(char* cube) {
	char tempFront[3] = {cube[0],cube[3], cube[6]};
	char tempBack[3] = {cube[20],cube[23], cube[26]};
	char tempUp[3] = {cube[36],cube[39], cube[42]};
	char tempDown[3] = {cube[45],cube[48], cube[51]};

	char tempLeft[9] {cube[33],cube[30], cube[27],
				cube[34],cube[31], cube[28],
				cube[35],cube[32], cube[29]};

	for (int i = 0; i < 9; i++) {
		cube[i + 27] = tempLeft[i];
	}
	for (int i = 0, j = 0; i < 9; i += 3, j++) {
		cube[i] = tempUp[j];
		cube[i + 20] = tempDown[j];
		cube[i + 36] = tempBack[j];
		cube[i + 45] = tempFront[j];
	}
}

void moveB(char* cube) {
	char tempRight[3] = {cube[11], cube[14], cube[17]};
	char tempLeft[3] = {cube[27], cube[30], cube[33]};
	char tempUp[3] = {cube[38], cube[37], cube[36]};
	char tempDown[3] = {cube[53], cube[52], cube[51]};

	char tempBack[9] = {cube[24], cube[21], cube[18],
						cube[25], cube[22], cube[19],
						cube[26], cube[23], cube[20]};
	for (int i = 0; i < 9; i++) {
		cube[i + 18] = tempBack[i];
	}
	for (int i = 0; i < 3; i++) {
		cube[i + 51] = tempLeft[i];
		cube[i + 36] = tempRight[i];
	}
	for (int i = 0, j = 0; i < 9; i += 3, j++) {
		cube[i + 11] = tempDown[j];
		cube[i + 27] = tempUp[j];
	}
}	

void moveB2 (char* cube) {
	moveB(cube);
	moveB(cube);
}
void moveL2 (char* cube) {
	moveL(cube);
	moveL(cube);
}
void moveR2 (char* cube) {
	moveR(cube);
	moveR(cube);
}
void moveF2 (char* cube) {
	moveF(cube);
	moveF(cube);
}
void moveU2 (char* cube) {
	moveU(cube);
	moveU(cube);
}
void moveD2 (char* cube) {
	moveD(cube);
	moveD(cube);
}

void moveBPrime(char* cube) {
	moveB(cube);
	moveB(cube);
	moveB(cube);
}

void moveLPrime(char* cube) {
	moveL(cube);
	moveL(cube);
	moveL(cube);
}

void moveRPrime(char* cube) {
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
    else if (moveStr == "L") moveLPrime(cube);
    else if (moveStr == "L'") moveL(cube);
    else if (moveStr == "B") moveBPrime(cube);
    else if (moveStr == "B'") moveB(cube);
    else if (moveStr == "U2") moveU2(cube);
    else if (moveStr == "F2") moveF2(cube);
    else if (moveStr == "R2") moveR2(cube);
    else if (moveStr == "D2") moveD2(cube);
    else if (moveStr == "L2") moveL2(cube);
    else if (moveStr == "B2") moveB2(cube);
}

bool isMovePrunable(const std::string& lastMove, const std::string& currentMove) {
    if (lastMove.front() == currentMove.front()) {
        if ((lastMove == "U" && currentMove == "U'") || (lastMove == "U'" && currentMove == "U") ||
            (lastMove == "R" && currentMove == "R'") || (lastMove == "R'" && currentMove == "R") ||
            (lastMove == "F" && currentMove == "F'") || (lastMove == "F'" && currentMove == "F") ||
            (lastMove == "D" && currentMove == "D'") || (lastMove == "D'" && currentMove == "D") ||
            (lastMove == "L" && currentMove == "L'") || (lastMove == "L'" && currentMove == "L") ||
            (lastMove == "B" && currentMove == "B'") || (lastMove == "B'" && currentMove == "B")) {
            return true;
        }
        else if (lastMove == currentMove) {
            return true;
        }
    }
    return false;
}

std::string encodeCurrentState(const char* cube) {
    std::string state;
    state.reserve(EDGE_COUNT * 2);
    for (int i = 0; i < EDGE_COUNT; ++i) {
        state.push_back(cube[edgeIndices[i][0]]);
        state.push_back(cube[edgeIndices[i][1]]);
    }
    return state;
}

bool iddfs(char* cube, int depth, int maxDepth, vector<string>& solution, 
			bool (*isSolved)(char*), const vector<pair<void(*)(char*), string>>& allowedMoves) {
	// if(isSolved(cube) || isFullySolved(cube)) {
	if(isSolved(cube)){
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

	for (auto& [moveFunc, moveStr] : allowedMoves) {
		 if (!solution.empty() && isMovePrunable(solution.back(), moveStr)) {
            continue;
        }
		moveFunc(cube);
		solution.push_back(moveStr);
		if (iddfs(cube, depth + 1, maxDepth, solution, isSolved, allowedMoves)) {
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
    else if (moveStr == "L") moveL(cube);
    else if (moveStr == "L'") moveLPrime(cube);
    else if (moveStr == "B") moveB(cube);
    else if (moveStr == "B'") moveBPrime(cube);
    else if (moveStr == "U2") moveU2(cube);
    else if (moveStr == "F2") moveF2(cube);
    else if (moveStr == "R2") moveR2(cube);
    else if (moveStr == "D2") moveD2(cube);
    else if (moveStr == "L2") moveL2(cube);
    else if (moveStr == "B2") moveB2(cube);
}

void solveGroup(char* cube, bool (*groupSolveCondition)(char*), const vector<pair<void(*)(char*), string>>& moves) {
    std::vector<string> solution;
    for (int i = 1; i < MAX_DEPTH; i++) {
        if (iddfs(cube, 0, i, solution, groupSolveCondition, moves))
            break;
    }
}

void solveCube(char* cube) {
    vector<pair<void(*)(char*), string>> group0Moves = {
		{moveU, "U"},
		{moveUPrime, "U'"},
		{moveF, "F"},
		{moveFPrime, "F'"},
		{moveR, "R"},
		{moveRPrime, "R'"},
		{moveD, "D"},
		{moveDPrime, "D'"},
		{moveL, "L"},
		{moveLPrime, "L'"},
		{moveB, "B"},
		{moveBPrime, "B'"},
		{moveU2, "U2"},
		{moveF2, "F2"},
		{moveR2, "R2"},
		{moveD2, "D2"},
		{moveL2, "L2"},
		{moveB2, "B2"},
    };

    solveGroup(cube, isGroup0Solved, group0Moves);
	printCube(cube);
	// if (isFullySolved(cube))
		// return;
    
    vector<pair<void(*)(char*), string>> group1Moves = { // no F, F', B, B'
		{moveU, "U"},
		{moveUPrime, "U'"},
		{moveR, "R"},
		{moveRPrime, "R'"},
		{moveD, "D"},
		{moveDPrime, "D'"},
		{moveL, "L"},
		{moveLPrime, "L'"},
		{moveU2, "U2"},
		{moveF2, "F2"},
		{moveR2, "R2"},
		{moveD2, "D2"},
		{moveL2, "L2"},
		{moveB2, "B2"},
    };
    
    // solveGroup(cube, isFullySolved, group1Moves);

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
	std::set<std::string> uniqueStates;
	if (argc > 1) {
		string scramble = av[1];
        vector<string> moves = splitString(scramble);
		for (const string& move : moves) {
            applyMove(cube, move);
        }
	}
	printCube(cube);
	solveCube(cube);
	cout << encodeCurrentState(cube) << endl;
    return 0;
}
