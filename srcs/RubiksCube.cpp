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

std::string RubiksCube::encodeEdgeOrientationsG0() const {
    std::string orientation;
    orientation.reserve(EDGE_COUNT);
    
    for (int i = 0; i < EDGE_COUNT; ++i) {
        std::pair<char, char> edgeColors = {state[edgeIndices[i][0]], state[edgeIndices[i][1]]};
        bool flipped = isEdgeFlippedG0(edgeColors);
        
        if (flipped) {
            orientation.push_back('1'); // Edge is flipped
        } else {
            orientation.push_back('0'); // Edge is not flipped
        }
    }
    
    return orientation;
}

int RubiksCube::calculateStateIndexG0(const RubiksCube& cube) {
	std::string edgeOrientation = cube.encodeEdgeOrientationsG0();
    int index = 0;
    for (size_t i = 0; i < edgeOrientation.size() - 1; ++i) {
        if (edgeOrientation[i] == '1') {
            index += (1 << i);
        }
    }
    return index;
}

//EDGE IS NOT FLIPPED IF WE CAN BRING IT TO ITS RIGHTFUL PLACE 
//WITHOUT F OR B (OR F' OR B')

//seems to me like the condition is the same for all up edges or down edges,
// inner cannot be white(down) or yellow(up)
// outer cannot be red(right) or orange(left) if we're considering that G1 is restricting F and B and front is blue and up yellow
// seems to me like its the same condition for literally all my edges
    // we use only the first 11 edges for index calculation, as it respects the parity rule
	// removes the issue about having 4096 entry

bool RubiksCube::isEdgeFlippedG0(std::pair<char, char> colors) {
	return (colors.second == 'Y' || colors.second == 'W' ||
				colors.first == 'O' || colors.first == 'R');
}

int RubiksCube::getCornerOrientationG1(int cornerIndex) const {
    const auto& indices = cornerIndices[cornerIndex];
    char colorU = state[indices[0]]; // top part
    char colorL = state[indices[1]]; // left part
    char colorR = state[indices[2]]; // right part

    if (colorU == 'W' || colorU == 'Y') {
        return 0; // No rotation needed
    } else if (colorL == 'W' || colorL == 'Y') {
        return 1; // 120 degrees rotation
    } else if (colorR == 'W' || colorR == 'Y') {
        return 2; // 240 degrees rotation
    }
    return -1;
}

bool RubiksCube::isEdgeInESliceG1(int edgeIndex) const {
    const std::set<std::pair<char, char>> validMiddleSliceColors = {
        {'B', 'R'}, {'R', 'B'},
        {'B', 'O'}, {'O', 'B'},
        {'G', 'R'}, {'R', 'G'},
        {'G', 'O'}, {'O', 'G'}
    };

    char color1 = state[edgeIndices[edgeIndex][0]];
    char color2 = state[edgeIndices[edgeIndex][1]];

    std::pair<char, char> edgeColors = {color1, color2};
    std::pair<char, char> edgeColorsReversed = {color2, color1};

    return validMiddleSliceColors.find(edgeColors) != validMiddleSliceColors.end() ||
           validMiddleSliceColors.find(edgeColorsReversed) != validMiddleSliceColors.end();
}

/*last corner's orientation is implicitly determined*/
int RubiksCube::encodeCornerOrientationsG1(const RubiksCube& cube) {
    int index = 0;
    int multiplier = 1;

    for (int i = 0; i < 7; i++) {
        int orientation = cube.getCornerOrientationG1(i);
        index += orientation * multiplier;
        multiplier *= 3;
    }

    return index;
}

int RubiksCube::encodeEdgeSlicePositionsG1(const RubiksCube& cube) {
    std::vector<int> positions;

	for (int i = 0; i < 12; i++) {
        if (cube.isEdgeInESliceG1(i)) {
            positions.push_back(i); 
        }
    }
	int index = 0, k = 4;
    for (unsigned long i = 0; i < positions.size(); ++i) {
		int bc = binomialCoefficient(11 - positions[i], k);
        index += bc;
		k--;
	}
	return index;
}

bool RubiksCube::isEdgeBlueOrGreenG2(int edgeIndex) const {
	const std::set<char> validSliceColors = {'G', 'B'};

    char color = state[edgeIndices[edgeIndex][1]];

    return validSliceColors.find(color) != validSliceColors.end();
}

int RubiksCube::encodeEdgeSlicePositionsG2(const RubiksCube& cube) {
    std::vector<int> positions;

	for (int i = 0; i < 8; i++) {
        if (cube.isEdgeBlueOrGreenG2(i)) {
            positions.push_back(i); 
        }
    }
	int index = 0, k = 4;
    for (unsigned long i = 0; i < positions.size(); ++i) {
		int bc = binomialCoefficient(7 - positions[i], k);
        index += bc;
		k--;
	}
	return index;
}

int RubiksCube::calculateStateIndexG1(const RubiksCube& cube) {
    int cornerIndex = encodeCornerOrientationsG1(cube);
    int edgeIndex = encodeEdgeSlicePositionsG1(cube);

    return cornerIndex * 495 + edgeIndex; // forgot why 495 and not 494 and would like to know why
}

int RubiksCube::calculateParityG2(const std::vector<int>& permutation) const {
	int parity = 0;
	for (int i = 0; i < permutation.size(); ++i) {
		for (int j = i + 1; j < permutation.size(); ++j) {
			parity ^= permutation[i] < permutation[j];
		}
	}
	return parity;
}

bool areDistinct(const std::pair<std::pair<char, char>, std::pair<char, char>>& pair1, const std::pair<std::pair<char, char>, std::pair<char, char>>& pair2) {
	return (pair1.first != pair2.first && pair1.second != pair2.second) &&
           (pair1.first != pair2.second && pair1.second != pair2.first);
}

int RubiksCube::calculateCornerIndexG2() const {
	int rank = 0;
	
	std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> cornerPairs = {
        // CornerPair0 - ULB/URF
        {{'O', 'G'}, {'R', 'B'}},
        // CornerPair1 - DLF/DRB
        {{'O', 'B'}, {'R', 'G'}},
        // CornerPair2 - URB/ULF
        {{'G', 'R'}, {'B', 'O'}},
        // CornerPair3 - DLB/DRF
        {{'G', 'O'}, {'B', 'R'}}
    };

	std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> remaining = {
		{{state[27], state[20]}, {state[9], state[2]}},    // {'O', 'G'}, {'R', 'B'}
		{{state[27], state[20]}, {state[35], state[6]}},   // {'O', 'G'}, {'O', 'B'}
		{{state[27], state[20]}, {state[17], state[24]}},  // {'O', 'G'}, {'R', 'G'}
		{{state[27], state[20]}, {state[18], state[11]}},  // {'O', 'G'}, {'G', 'R'}
		{{state[27], state[20]}, {state[8], state[15]}},   // {'O', 'G'}, {'B', 'O'}
		{{state[27], state[20]}, {state[26], state[33]}},  // {'O', 'G'}, {'G', 'O'}
		{{state[27], state[20]}, {state[0], state[29]}},   // {'O', 'G'}, {'B', 'R'}

		{{state[9], state[2]}, {state[35], state[6]}},     // {'R', 'B'}, {'O', 'B'}
		{{state[9], state[2]}, {state[17], state[24]}},    // {'R', 'B'}, {'R', 'G'}
		{{state[9], state[2]}, {state[18], state[11]}},    // {'R', 'B'}, {'G', 'R'}
		{{state[9], state[2]}, {state[8], state[15]}},     // {'R', 'B'}, {'B', 'O'}
		{{state[9], state[2]}, {state[26], state[33]}},    // {'R', 'B'}, {'G', 'O'}
		{{state[9], state[2]}, {state[0], state[29]}},     // {'R', 'B'}, {'B', 'R'}

		{{state[35], state[6]}, {state[17], state[24]}},   // {'O', 'B'}, {'R', 'G'}
		{{state[35], state[6]}, {state[18], state[11]}},   // {'O', 'B'}, {'G', 'R'}
		{{state[35], state[6]}, {state[8], state[15]}},    // {'O', 'B'}, {'B', 'O'}
		{{state[35], state[6]}, {state[26], state[33]}},   // {'O', 'B'}, {'G', 'O'}
		{{state[35], state[6]}, {state[0], state[29]}},    // {'O', 'B'}, {'B', 'R'}

		{{state[17], state[24]}, {state[18], state[11]}},  // {'R', 'G'}, {'G', 'R'}
		{{state[17], state[24]}, {state[8], state[15]}},   // {'R', 'G'}, {'B', 'O'}
		{{state[17], state[24]}, {state[26], state[33]}},  // {'R', 'G'}, {'G', 'O'}
		{{state[17], state[24]}, {state[0], state[29]}},   // {'R', 'G'}, {'B', 'R'}

		{{state[18], state[11]}, {state[8], state[15]}},   // {'G', 'R'}, {'B', 'O'}
		{{state[18], state[11]}, {state[26], state[33]}},  // {'G', 'R'}, {'G', 'O'}
		{{state[18], state[11]}, {state[0], state[29]}},   // {'G', 'R'}, {'B', 'R'}

		{{state[8], state[15]}, {state[26], state[33]}},   // {'B', 'O'}, {'G', 'O'}
		{{state[8], state[15]}, {state[0], state[29]}},    // {'B', 'O'}, {'B', 'R'}

		{{state[26], state[33]}, {state[0], state[29]}}    // {'G', 'O'}, {'B', 'R'}
	};


	int bases[3];
	bases[2] = 1; // 2C2.

    for (int i = 1; i >= 0; --i) bases[i] = bases[i + 1] * choose((6) - 2*i, 2);

	unsigned numRemaining = 28;

	for (unsigned n = 0; n < 3; ++n) {
		unsigned remainingInd = 0;
		const auto& sPair = cornerPairs[n];

		for (unsigned r = 0; r < numRemaining; ++r) {
            const auto& rPair = remaining[r];

            if ((sPair.first == rPair.first && sPair.second == rPair.second) ||
					(sPair.first == rPair.second && sPair.second == rPair.first)) {
                rank += r * bases[n];
                break; // Found the match, stop searching
            }
        }

        std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> newRemaining;
        for (unsigned r = 0; r < numRemaining; ++r) {
            if (areDistinct(sPair, remaining[r])) {
                newRemaining.push_back(remaining[r]);
            }
        }
        remaining = newRemaining;
        numRemaining = remaining.size();
	}

	return rank;
}

std::vector<int> RubiksCube::getCornerPermutationG2() const {
	std::vector<int> cornerPermutation(CORNER_COUNT);
	for (int i = 0; i < CORNER_COUNT; ++i) {
		for (int j = 0; j < CORNER_COUNT; ++j) {
			if (state[cornerIndices[j][0]] == edgesBaseColours[i].first && 
				state[cornerIndices[j][1]] == edgesBaseColours[i].second) {
				cornerPermutation[i] = j;
				break;
			}
		}
	}
	return cornerPermutation;
}

int RubiksCube::calculateStateIndexG2(const RubiksCube& cube) {
    int cornerIndex = cube.calculateCornerIndexG2();
    int edgeIndex = encodeEdgeSlicePositionsG2(cube);

    std::array<int, 4> edgeCombo;
    unsigned edgeComboInd = 0;

    for (int i = 0; i < 8 && edgeComboInd < 4; ++i) {
        if (cube.isEdgeBlueOrGreenG2(i)) {
            edgeCombo[edgeComboInd++] = i;
        }
    }

    std::vector<int> cornerPermutation = cube.getCornerPermutationG2();
    int parity = cube.calculateParityG2(cornerPermutation);  // Calculate parity from corner permutation
	return (edgeIndex * 2520 + cornerIndex) * 2 + parity;
}

int getEdgeIndexFromColors(std::pair<char, char> edge) {
	if (edge.first == 'Y' && edge.second == 'G') return 0;	
	else if (edge.first == 'Y' && edge.second == 'B') return 1;	
	else if (edge.first == 'W' && edge.second == 'B') return 2;	
	else if (edge.first == 'W' && edge.second == 'G') return 3;	

	if (edge.first == 'Y' && edge.second == 'R') return 0;	
	else if (edge.first == 'Y' && edge.second == 'O') return 1;	
	else if (edge.first == 'W' && edge.second == 'O') return 2;	
	else if (edge.first == 'W' && edge.second == 'R') return 3;	

	if (edge.first == 'B' && edge.second == 'R') return 0;	
	else if (edge.first == 'B' && edge.second == 'O') return 1;
	else if (edge.first == 'G' && edge.second == 'R') return 2;
	else if (edge.first == 'G' && edge.second == 'O') return 3;

	std::cout << "fatallry errored" << std::endl;
	exit(1);
	return -1;
}


int	RubiksCube::permIndexer(std::array<uint8_t, 4>& perm) const {
	std::array<uint32_t, (1 << 4) - 1> onesCountLookup;
	for (uint32_t i = 0; i < (1 << 4) - 1; ++i)
    {
        std::bitset<4> bits(i);
        onesCountLookup[i] = bits.count();
    }

	std::array<uint32_t, 4> lehmer;

	// Set of "seen" digits in the permutation.
	std::bitset<4> seen;

	// The first digit of the Lehmer code is always the first digit of
	// the permutation.
	lehmer[0] = perm[0];

	// Mark the digit as seen (std::bitset uses right-to-left indexing).
	seen[4 - 1 - perm[0]] = 1;

	for (uint32_t i = 1; i < 4; ++i)
	{
	seen[4 - 1 - perm[i]] = 1;

	// The number of "seen" digits to the left of this digit is the
	// count of ones left of this digit.
	uint32_t numOnes = onesCountLookup[seen.to_ulong() >> (4 - perm[i])];

	lehmer[i] = perm[i] - numOnes;
	}

	// Convert the Lehmer code to base-10.
	uint32_t index = 0;

	for (uint32_t i = 0; i < 4; ++i)
	// index += lehmer[i] * this->factorials[i];
	index += lehmer[i] * pick(4 - 1 - i, 4 - 1 - i); 

	return index;
}

int	RubiksCube::partialPermIndexer(std::array<uint8_t, 2>& perm) const {
	std::array<uint32_t, (1 << 4) - 1> onesCountLookup;
	for (uint32_t i = 0; i < (1 << 4) - 1; ++i)
    {
        std::bitset<4> bits(i);
        onesCountLookup[i] = bits.count();
    }

	std::array<uint32_t, 2> lehmer;

	// Set of "seen" digits in the permutation.
	std::bitset<4> seen;

	// The first digit of the Lehmer code is always the first digit of
	// the permutation.
	lehmer[0] = perm[0];

	// Mark the digit as seen (std::bitset uses right-to-left indexing).
	seen[4 - 1 - perm[0]] = 1;

	for (uint32_t i = 1; i < 2; ++i)
	{
		seen[4 - 1 - perm[i]] = 1;

		// The number of "seen" digits to the left of this digit is the
		// count of ones left of this digit.
		uint32_t numOnes = onesCountLookup[seen.to_ulong() >> (4 - perm[i])];

		lehmer[i] = perm[i] - numOnes;
	}

	// Convert the Lehmer code to base-10.
	uint32_t index = 0;

	for (uint32_t i = 0; i < 2; ++i)
	// index += lehmer[i] * this->factorials[i];
	index += lehmer[i] * pick(4 - 1 - i, 2 - 1 - i); 

	return index;
}

int RubiksCube::calculateEdgeIndexG3() const {
	std::array<uint8_t, 4> m;
	std::array<uint8_t, 4> s;
	std::array<uint8_t, 2> e;

	for (int i = 0; i < 10; i++) {
		std::pair <char, char> colorPair = {state[edgeIndicesG3[i][0]], state[edgeIndicesG3[i][1]]};
		int color = getEdgeIndexFromColors(colorPair);
		if (i < 4) m[i] = color;
		else if (i < 8) s[i - 4] = color;
		else e[i - 8] = color;
	}

	return permIndexer(m) * 288 + permIndexer(s) * 12 + partialPermIndexer(e);
}

int getCornerIndexFromColors(std::pair<char, char> corner) {
	if (corner.first == 'O' && corner.second == 'G') return 0;
	else if (corner.first == 'R' && corner.second == 'B') return 1;
	else if (corner.first == 'O' && corner.second == 'B') return 2;
	else if (corner.first == 'R' && corner.second == 'G') return 3;
	else if (corner.first == 'G' && corner.second == 'R') return 0;
	else if (corner.first == 'B' && corner.second == 'O') return 1;
	else if (corner.first == 'G' && corner.second == 'O') return 2;
	else if (corner.first == 'B' && corner.second == 'R') return 3;

	std::cout << "bro the fuck" << std::endl;
	std::cout << "corner.first: " << corner.first << std::endl;
	std::cout << "corner.second: " << corner.second << std::endl;
	exit(1);
}

int RubiksCube::calculateCornerIndexG3() const {
	std::array<uint8_t, 4> tetrad1;

	for (int i = 0; i < 4; i++) {
		std::pair <char, char> colorPair = {state[cornerIndicesG3[i][1]], state[cornerIndicesG3[i][2]]};
		int color = getCornerIndexFromColors(colorPair);
		tetrad1[i] = color;
	}

	std::pair <char, char> urbColors = {state[cornerIndicesG3[4][1]], state[cornerIndicesG3[4][2]]};

	int tetradRank = permIndexer(tetrad1);
	return tetradRank * 4 + getCornerIndexFromColors(urbColors);
}

int	RubiksCube::calculateStateIndexG3(const RubiksCube& cube) {
	int edgeIndex = cube.calculateEdgeIndexG3();
	int cornerIndex = cube.calculateCornerIndexG3();

	return edgeIndex * 96 + cornerIndex;
}
