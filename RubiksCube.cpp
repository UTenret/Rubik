#include "RubiksCube.hpp"

RubiksCube::RubiksCube(const std::string& initialState) : state(initialState) {}

const std::string& RubiksCube::getState() const {
	return state;
}

void RubiksCube::applyMove(std::string& cube, const string& moveStr) {
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

void RubiksCube::moveB2 (std::string& cube) {
	moveB(cube);
	moveB(cube);
}
void RubiksCube::moveL2 (std::string& cube) {
	moveL(cube);
	moveL(cube);
}
void RubiksCube::moveR2 (std::string& cube) {
	moveR(cube);
	moveR(cube);
}
void RubiksCube::moveF2 (std::string& cube) {
	moveF(cube);
	moveF(cube);
}
void RubiksCube::moveU2 (std::string& cube) {
	moveU(cube);
	moveU(cube);
}
void RubiksCube::moveD2 (std::string& cube) {
	moveD(cube);
	moveD(cube);
}

void RubiksCube::moveBPrime(std::string& cube) {
	moveB(cube);
	moveB(cube);
	moveB(cube);
}

void RubiksCube::moveLPrime(std::string& cube) {
	moveL(cube);
	moveL(cube);
	moveL(cube);
}

void RubiksCube::moveRPrime(std::string& cube) {
	moveR(cube);
	moveR(cube);
	moveR(cube);
}

void RubiksCube::moveUPrime(std::string& cube) {
	moveU(cube);
	moveU(cube);
	moveU(cube);
}

void RubiksCube::moveFPrime(std::string& cube) {
	moveF(cube);
	moveF(cube);
	moveF(cube);
}

void RubiksCube::moveDPrime(std::string& cube) {
	moveD(cube);
	moveD(cube);
	moveD(cube);
}

void RubiksCube::applyInverseMove(std::string& cube, const string& moveStr) {
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

void RubiksCube::moveD(std::string& cube) {
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

void RubiksCube::moveF(std::string& cube) {
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

void RubiksCube::moveU(std::string& cube) {
	char tempFront[3] = {cube[0], cube[1], cube[2]};
	char tempRight[3] = {cube[9], cube[10], cube[11]};
	char tempBack[3] = {cube[18], cube[19], cube[20]};
	char tempLeft[3] = {cube[27], cube[28], cube[29]};

	char tempU[9] = {cube[42],cube[39],cub?>>ee[36],
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

void RubiksCube::moveR(std::string& cube) {
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

void RubiksCube::moveL(std::string& cube) {
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

void RubiksCube::moveB(std::string& cube) {
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

std::string RubiksCube::colorize(char color) {    
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

void RubiksCube::printCube(const std::string& cube) {
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

bool RubiksCube::isSolved(const std::string& cube) const {
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