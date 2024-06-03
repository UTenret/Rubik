#include "RubiksCube.hpp"

RubiksCube::RubiksCube(const std::string& initialState) : state(initialState) {}

RubiksCube::RubiksCube(const RubiksCube& other) : state(other.state) {}

const std::string& RubiksCube::getState() const {
	return state;
}

void RubiksCube::applyMove(const std::string& moveStr) {
	if (moveStr == "U") moveU();
    else if (moveStr == "U'") moveUPrime();
    else if (moveStr == "F") moveF();
    else if (moveStr == "F'") moveFPrime();
    else if (moveStr == "R") moveR();
    else if (moveStr == "R'") moveRPrime();
    else if (moveStr == "D") moveD();
    else if (moveStr == "D'") moveDPrime();
    else if (moveStr == "L") moveL();
    else if (moveStr == "L'") moveLPrime();
    else if (moveStr == "B") moveB();
    else if (moveStr == "B'") moveBPrime();
    else if (moveStr == "U2") moveU2();
    else if (moveStr == "F2") moveF2();
    else if (moveStr == "R2") moveR2();
    else if (moveStr == "D2") moveD2();
    else if (moveStr == "L2") moveL2();
    else if (moveStr == "B2") moveB2();
}

void RubiksCube::moveB2 () {
	moveB();
	moveB();
}
void RubiksCube::moveL2 () {
	moveL();
	moveL();
}
void RubiksCube::moveR2 () {
	moveR();
	moveR();
}
void RubiksCube::moveF2 () {
	moveF();
	moveF();
}
void RubiksCube::moveU2 () {
	moveU();
	moveU();
}
void RubiksCube::moveD2 () {
	moveD();
	moveD();
}

void RubiksCube::moveBPrime() {
	moveB();
	moveB();
	moveB();
}

void RubiksCube::moveLPrime() {
	moveL();
	moveL();
	moveL();
}

void RubiksCube::moveRPrime() {
	moveR();
	moveR();
	moveR();
}

void RubiksCube::moveUPrime() {
	moveU();
	moveU();
	moveU();
}

void RubiksCube::moveFPrime() {
	moveF();
	moveF();
	moveF();
}

void RubiksCube::moveDPrime() {
	moveD();
	moveD();
	moveD();
}

void RubiksCube::applyInverseMove(const std::string& moveStr) {
    if (moveStr == "U") moveUPrime();
    else if (moveStr == "U'") moveU();
    else if (moveStr == "F") moveFPrime();
    else if (moveStr == "F'") moveF();
    else if (moveStr == "R") moveRPrime();
    else if (moveStr == "R'") moveR();
    else if (moveStr == "D") moveDPrime();
    else if (moveStr == "D'") moveD();
    else if (moveStr == "L") moveLPrime();
    else if (moveStr == "L'") moveL();
    else if (moveStr == "B") moveBPrime();
    else if (moveStr == "B'") moveB();
    else if (moveStr == "U2") moveU2();
    else if (moveStr == "F2") moveF2();
    else if (moveStr == "R2") moveR2();
    else if (moveStr == "D2") moveD2();
    else if (moveStr == "L2") moveL2();
    else if (moveStr == "B2") moveB2();
}

void RubiksCube::scramble(const std::string& moves) {
    std::istringstream iss(moves);
    std::string move;
    while (iss >> move) {
        applyMove(move);
    }
}

void RubiksCube::moveD() {
	char tempFront[3] = {state[6], state[7], state[8]};
	char tempRight[3] = {state[15], state[16], state[17]};
	char tempBack[3] = {state[24], state[25], state[26]};
	char tempLeft[3] = {state[33], state[34], state[35]};

	char tempDown[9] = {state[51], state[48], state[45],
						state[52], state[49], state[46],
						state[53], state[50], state[47]};
	for (int i = 0; i < 9; i++) {
		state[i + 45] = tempDown[i];
	}
	for (int i = 0; i < 3; i++) {
		state[i + 6] = tempLeft[i];
		state[i + 15] = tempFront[i];
		state[i + 24] = tempRight[i];
		state[i + 33] = tempBack[i];
	}
		
}

void RubiksCube::moveF() {
	char tempLeft[3] = {state[29], state[32], state[35]};
	char tempRight[3] = {state[9], state[12], state[15]};
	char tempUp[3] = {state[42], state[43], state[44]};
	char tempDown[3] = {state[45], state[46], state[47]};

	char tempFront[9] = {state[6], state[3], state[0],
						state[7], state[4], state[1],
						state[8], state[5], state[2]};

	for (int i = 0; i < 9; i++) {
		state[i] = tempFront[i];
	}
	for (int i = 0, j = 0; i < 9; i += 3, j++) {
		state[i + 9] = tempUp[j];
		state[i + 29] = tempDown[j];
	}
	state[42] = tempLeft[2];
	state[43] = tempLeft[1];
	state[44] = tempLeft[0];
	state[45] = tempRight[2];
	state[46] = tempRight[1];
	state[47] = tempRight[0];
}

void RubiksCube::moveU() {
	char tempFront[3] = {state[0], state[1], state[2]};
	char tempRight[3] = {state[9], state[10], state[11]};
	char tempBack[3] = {state[18], state[19], state[20]};
	char tempLeft[3] = {state[27], state[28], state[29]};

	char tempU[9] = {state[42],state[39],state[36],
					state[43],state[40],state[37],
					state[44],state[41],state[38]};
	for (int i = 0; i < 9; i++) {
		state[i + 36] = tempU[i];						//ROTATE THE UP
	}
	for (int i = 0; i < 3; i++) {						// rotate the top row
		state[i] = tempRight[i];
		state[i + 9] = tempBack[i];
		state[i + 18] = tempLeft[i];
		state[i + 27] = tempFront[i];
	}
}

void RubiksCube::moveR() {
	char tempFront[3] = {state[2],state[5],state[8]};
	char tempUp[3] = {state[44],state[41],state[38]};
	char tempDown[3] = {state[47],state[50],state[53]};
	char tempBack[3] = {state[24],state[21],state[18]};

	char tempRight[9] = {state[15], state[12], state[9],
						state[16], state[13], state[10],
						state[17], state[14], state[11]};

	for (int i = 0; i < 9; i++) {
		state[i + 9] = tempRight[i];
	}
	for (int i = 0, j = 0; i < 9; i += 3, j++) {
		state[i + 2] = tempDown[j];
		state[i + 18] = tempUp[j];
		state[i + 38] = tempFront[j];
		state[i + 47] = tempBack[j];
	}
}

void RubiksCube::moveL() {
	char tempFront[3] = {state[0],state[3], state[6]};
	char tempBack[3] = {state[26],state[23], state[20]};
	char tempUp[3] = {state[36],state[39], state[42]};
	char tempDown[3] = {state[51],state[48], state[45]};

	char tempLeft[9] {state[33],state[30], state[27],
				state[34],state[31], state[28],
				state[35],state[32], state[29]};

	for (int i = 0; i < 9; i++) {
		state[i + 27] = tempLeft[i];
	}
	for (int i = 0, j = 0; i < 9; i += 3, j++) {
		state[i] = tempUp[j];
		state[i + 20] = tempDown[j];
		state[i + 36] = tempBack[j];
		state[i + 45] = tempFront[j];
	}
}

void RubiksCube::moveB() {
	char tempRight[3] = {state[11], state[14], state[17]};
	char tempLeft[3] = {state[27], state[30], state[33]};
	char tempUp[3] = {state[38], state[37], state[36]};
	char tempDown[3] = {state[53], state[52], state[51]};

	char tempBack[9] = {state[24], state[21], state[18],
						state[25], state[22], state[19],
						state[26], state[23], state[20]};
	for (int i = 0; i < 9; i++) {
		state[i + 18] = tempBack[i];
	}
	for (int i = 0; i < 3; i++) {
		state[i + 51] = tempLeft[i];
		state[i + 36] = tempRight[i];
	}
	for (int i = 0, j = 0; i < 9; i += 3, j++) {
		state[i + 11] = tempDown[j];
		state[i + 27] = tempUp[j];
	}
}

std::string RubiksCube::colorize(const char color) const {    
    switch (color) {
        case 'W': return "\033[97mW\033[0m"; // White
        case 'Y': return "\033[93mY\033[0m"; // Yellow
        case 'R': return "\033[91mR\033[0m"; // Red
        case 'O': return "\033[38;5;208mO\033[0m"; // Orange
        case 'G': return "\033[92mG\033[0m"; // Green
        case 'B': return "\033[94mB\033[0m"; // Blue
        default: return std::string(1, color);
    }
}

void RubiksCube::printCube() const {
    std::cout << "|||PRINTING CUBE|||" << std::endl;
    std::cout << std::endl;
    
    // Print U
	std::cout << "    ";
    for (int i = 36; i < 45; i++) {
        std::cout << colorize(state[i]);
        if ((i + 1) % 3 == 0) std::cout << std::endl << "    ";
    }
    std::cout << std::endl;

    // Print LFR
    for (int row = 0; row < 3; row++) {
        // Print L
        for (int i = 27 + row * 3; i < 30 + row * 3; i++) {
            std::cout << colorize(state[i]);
        }
        std::cout << " ";
        // Print F
        for (int i = 0 + row * 3; i < 3 + row * 3; i++) {
            std::cout << colorize(state[i]);
        }
        std::cout << " ";
        // Print R
        for (int i = 9 + row * 3; i < 12 + row * 3; i++) {
            std::cout << colorize(state[i]);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Print D
	std::cout << "    ";
    for (int i = 45; i < 54; i++) {
        std::cout << colorize(state[i]);
        if ((i + 1) % 3 == 0) std::cout << std::endl << "    ";
    }
    std::cout << std::endl;

    // Print B
	std::cout << "    ";
	for (int i = 18; i < 27; i++) {
        std::cout << colorize(state[i]);
        if ((i + 1) % 3 == 0 && (i != 26)) std::cout << std::endl << "    ";
    }
	std::cout << std::endl;
}

void RubiksCube::printState() const {
	std::cout << "Current cube state: " << state << std::endl;
}

bool RubiksCube::isSolved() const {
	for (int i = 0; i < 9; i++) {
		if (state[i] != 'B')
			return false;
	}
	for (int i = 9; i < 18; i++) {
		if (state[i] != 'R')
			return false;
	}
	for (int i = 18; i < 27; i++) {
		if (state[i] != 'G')
			return false;
	}
	for (int i = 27; i < 36; i++) {
		if (state[i] != 'O')
			return false;
	}
	for (int i = 36; i < 45; i++) {
		if (state[i] != 'Y')
			return false;
	}
	for (int i = 45; i < 54; i++) {
		if (state[i] != 'W')
			return false;
	}
	return true;
}
