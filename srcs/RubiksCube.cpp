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

std::string RubiksCube::encodeEdgeOrientationsG0(const std::string& cubeState) {
    std::string orientation;
    orientation.reserve(EDGE_COUNT);
    
    for (int i = 0; i < EDGE_COUNT; ++i) {
        std::pair<char, char> edgeColors = {cubeState[edgeIndices[i][0]], cubeState[edgeIndices[i][1]]};
        bool flipped = isEdgeFlippedG0(edgeColors);
        
        // // Debugging output
        // std::cout << "Edge " << i << ": [" << edgeIndices[i][0] << ", " << edgeIndices[i][1] << "] "
        //           << "(" << edgeColors.first << ", " << edgeColors.second << ") "
        //           << "Flipped: " << (flipped ? "Yes" : "No") << "\n";

        if (flipped) {
            orientation.push_back('1'); // Edge is flipped
        } else {
            orientation.push_back('0'); // Edge is not flipped
        }
    }
    
    // std::cout << "Encoded Orientation: " << orientation << "\n";
    
    return orientation;
}

int RubiksCube::calculateStateIndexG0(const std::string& edgeOrientation) {
    int index = 0;
    for (size_t i = 0; i < edgeOrientation.size() - 1; ++i) {
        if (edgeOrientation[i] == '1') {
            index += (1 << i);
        }
    }
	// std::cout << "index: " << index << std::endl;
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

int binomialCoefficient(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    int num = 1, denom = 1;
    for (int i = 0; i < k; ++i) {
        num *= (n - i);
        denom *= (i + 1);
    }
    return num / denom;
}

int RubiksCube::getCornerOrientationG1(int cornerIndex) const {
    const auto& indices = cornerIndices[cornerIndex];
    char colorU = state[indices[0]]; // top part
    char colorL = state[indices[1]]; // left part
    char colorR = state[indices[2]]; // right part

    // Assuming 'W' and 'Y' are up and down colors, respectively
    if (colorU == 'W' || colorU == 'Y') {
        return 0; // No rotation needed
    } else if (colorL == 'W' || colorL == 'Y') {
        return 1; // 120 degrees rotation
    } else if (colorR == 'W' || colorR == 'Y') {
        return 2; // 240 degrees rotation
    }
	std::cout << "colorL: " << colorL << std::endl;
	std::cout << "colorR: " << colorR << std::endl;
	std::cout << "colorU: " << colorU << std::endl;
    return -1; // Error case if something unexpected
}

int RubiksCube::getCornerTetradPosG2(int cornerIndex) const {
    const auto& indices = cornerIndices[cornerIndex];
    char colorL = state[indices[1]]; // left part
    char colorR = state[indices[2]]; // right part

	// std::cout << "colorL: " << colorL << std::endl;
	// std::cout << "colorR: " << colorR << std::endl;
	// std::cout << "colorU: " << colorU << std::endl;

	const std::set<std::pair<char, char>> validCornerColors = {
        {'B', 'O'},
        {'G', 'R'},
        {'G', 'O'},
        {'B', 'R'},
    };

    std::pair<char, char> edgeColors = {colorL, colorR};

    return validCornerColors.find(edgeColors) != validCornerColors.end();
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


int RubiksCube::encodeCornerOrientationsG1(const RubiksCube& cube) {
    int index = 0;
    int multiplier = 1;
    for (int i = 0; i < 7; i++) {  // Assuming the last corner's orientation is implicitly determined
		// std::cout << "i: " << i << std::endl;
		// std::cout << "multiplier: " << multiplier << std::endl;
        int orientation = cube.getCornerOrientationG1(i);
		// std::cout << "orientation: " << orientation << std::endl;
        index += orientation * multiplier;
		// std::cout << "index: " << index << std::endl;
        multiplier *= 3;
    }
    return index;
}

int RubiksCube::encodeEdgeSlicePositionsG1(const RubiksCube& cube) {
    std::vector<int> positions;

	for (int i = 0; i < 12; i++) {
        if (cube.isEdgeInESliceG1(i)) {
			// std::cout << "middle edge is at position: " << i << std::endl;
            positions.push_back(i); 
        }
    }
	// positions.push_back(6);
	// positions.push_back(9);
	// positions.push_back(10);
	// positions.push_back(11);
	int index = 0, k = 4;
    for (unsigned long i = 0; i < positions.size(); ++i) {
		// std::cout << "bc: " << bc << std::endl;
		// std::cout << "k: " << k << std::endl;
		// std::cout << "positions[i]: " << positions[i] << std::endl;
		int bc = binomialCoefficient(11 - positions[i], k);
        index += bc;
		k--;
	}
	// std::cout << "index: " << index << std::endl;
	// exit(1);
	return index;
}

bool RubiksCube::isEdgeBlueOrGreenG2(int edgeIndex) const {
	const std::set<char> validSliceColors = {'G', 'B'};

    // char color1 = state[edgeIndices[edgeIndex][0]];
    char color = state[edgeIndices[edgeIndex][1]];

    return validSliceColors.find(color) != validSliceColors.end();
}

int RubiksCube::encodeEdgeSlicePositionsG2(const RubiksCube& cube) {
    std::vector<int> positions;

	for (int i = 0; i < 8; i++) {
        if (cube.isEdgeBlueOrGreenG2(i)) {
			// std::cout << "green or blue edge is at position: " << i << std::endl;
            positions.push_back(i); 
        }
    }
	// positions.push_back(6);
	// positions.push_back(9);
	// positions.push_back(10);
	// positions.push_back(11);
	int index = 0, k = 4;
    for (unsigned long i = 0; i < positions.size(); ++i) {
		// std::cout << "bc: " << bc << std::endl;
		// std::cout << "k: " << k << std::endl;
		// std::cout << "positions[i]: " << positions[i] << std::endl;
		int bc = binomialCoefficient(7 - positions[i], k);
        index += bc;
		k--;
	}
	// std::cout << "index: " << index << std::endl;
	// exit(1);
	return index;
}

int RubiksCube::encodeCornerTetradG2(const RubiksCube& cube) {
    std::vector<int> positions;

	for (int i = 0; i < 8; i++) {
        if (cube.getCornerTetradPosG2(i)) {
			// std::cout << "green or blue edge is at position: " << i << std::endl;
            positions.push_back(i); 
        }
    }
	// positions.push_back(6);
	// positions.push_back(9);
	// positions.push_back(10);
	// positions.push_back(11);
	int index = 0, k = 4;
    for (unsigned long i = 0; i < positions.size(); ++i) {
		// std::cout << "bc: " << bc << std::endl;
		// std::cout << "k: " << k << std::endl;
		// std::cout << "positions[i]: " << positions[i] << std::endl;
		int bc = binomialCoefficient(7 - positions[i], k);
        index += bc;
		k--;
	}
	// std::cout << "index: " << index << std::endl;
	// exit(1);
	return index;
}

int RubiksCube::calculateStateIndexG1(const RubiksCube& cube) {
    int cornerIndex = encodeCornerOrientationsG1(cube);
    int edgeIndex = encodeEdgeSlicePositionsG1(cube);

	// std::cout << "corner index = " << cornerIndex << std::endl;
	// std::cout << "edgeIndex = " << edgeIndex << std::endl;
	// std::cout << "cornerIndex * 495 + edgeIndex = " << cornerIndex * 495 + edgeIndex << std::endl;
	// std::cout << "cornerIndex: " << cornerIndex << std::endl;
	// std::cout << "cornerIndex: " << cornerIndex << std::endl;
    // return cornerIndex;
	// if (cornerIndex * 495 + edgeIndex == 5)
	// 	std::cout << "hello im " << cornerIndex * 495 + edgeIndex << std::endl;
    return cornerIndex * 495 + edgeIndex; // forgot why 495 and not 494 and would like to know why
    // return edgeIndex;
}

std::vector<int> RubiksCube::getCornerPermutationG2() const {
    std::vector<int> permutation(CORNER_COUNT);
    for (int i = 0; i < CORNER_COUNT; i++) {
        // Decode the corner position from the state vector
        // Assuming state stores corner positions in the range [12, 19]
        permutation[i] = std::find(cornerIndices[i], cornerIndices[i] + 3, state[12 + i]) - cornerIndices[i];
    }
    return permutation;
}

std::vector<int> RubiksCube::getEdgePermutationG2() const {
    std::vector<int> edgePermutation(EDGE_COUNT, -1);
    std::vector<std::pair<char, char>> targetEdgeColors = {
        {'Y', 'G'}, {'Y', 'R'}, {'Y', 'B'}, {'Y', 'O'},
        {'W', 'R'}, {'W', 'B'}, {'W', 'O'}, {'W', 'G'},
        {'B', 'R'}, {'B', 'O'}, {'G', 'R'}, {'G', 'O'}
    };

    // Extract current edge colors from cube state
	// printState();
    std::vector<std::pair<char, char>> currentEdgeColors(EDGE_COUNT);
    for (int i = 0; i < EDGE_COUNT; i++) {
        currentEdgeColors[i] = {state[edgeIndices[i][0]], state[edgeIndices[i][1]]};
		// std::cout << "currentEdgeColors[i].first: " << currentEdgeColors[i].first << std::endl;
		// std::cout << "currentEdgeColors[i].second: " << currentEdgeColors[i].second << std::endl;
		// std::cout << "edgeIndices[i][0]: " << edgeIndices[i][0] << std::endl;
		// std::cout << "edgeIndices[i][1]: " << edgeIndices[i][1] << std::endl;
		// std::cout << "state[edgeIndices[i][0]]: " << state[edgeIndices[i][0]] << std::endl;
		// std::cout << "state[edgeIndices[i][1]]: " << state[edgeIndices[i][1]] << std::endl;
		// std::cout << "i: " << i << std::endl;
    }

    // Match current edges against target configuration
    for (int i = 0; i < EDGE_COUNT; i++) {
        for (int j = 0; j < EDGE_COUNT; j++) {
            if ((currentEdgeColors[i] == targetEdgeColors[j]) ||
                (std::make_pair(currentEdgeColors[i].second, currentEdgeColors[i].first) == targetEdgeColors[j])) {
                edgePermutation[i] = j;
                break;
            }
        }
    }

    // Debug print the computed edge permutation
    // std::cout << "Computed Edge Permutation: ";
    // for (int perm : edgePermutation) {
    //     std::cout << perm << " ";
    // }
    // std::cout << std::endl;

    return edgePermutation;
}

int RubiksCube::calculateParityG2(const std::vector<int>& permutation) const {
    int parity = 0;
    std::vector<bool> visited(permutation.size(), false);
    for (int start = 0; start < permutation.size(); start++) {
        if (!visited[start]) {
            int current = start;
            int cycleLength = 0;
            // std::cout << "Cycle start at index " << start << ": ";
            // Follow the permutation until we come back to the start
            do {
                visited[current] = true;
                // std::cout << current << " -> ";
                current = permutation[current];
                cycleLength++;
            } while (current != start && !visited[current]);
            // std::cout << "end (" << cycleLength << " elements)" << std::endl;
            if (cycleLength > 1) {
                parity += (cycleLength - 1);  // Each cycle of size n has (n-1) transpositions
            }
        }
    }
    // std::cout << "Total parity: " << parity << " (mod 2 = " << (parity % 2) << ")" << std::endl;
    return parity % 2;  // Return 0 if even, 1 if odd
}

uint32_t factorial(uint32_t n)
{
  return n <= 1 ? 1 : n * factorial(n - 1);
}

uint32_t choose(uint32_t n, uint32_t k)
{
  return (n < k)
    ? 0
    : factorial(n) / (factorial(n - k) * factorial(k));
}

bool areDistinct(const std::pair<std::pair<char, char>, std::pair<char, char>>& pair1, const std::pair<std::pair<char, char>, std::pair<char, char>>& pair2) {
    // Check if any corner in pair1 is the same as any corner in pair2
	// std::cerr << "pair1.first: " << pair1.first.first << std::endl;
	// std::cerr << "pair1.first: " << pair1.first.second << std::endl;
	// std::cerr << "pair1.second: " << pair1.second.first << std::endl;
	// std::cerr << "pair1.second: " << pair1.second.second << std::endl;

	// std::cerr << "pair2.first: " << pair2.first.first << std::endl;
	// std::cerr << "pair2.first: " << pair2.first.second << std::endl;
	// std::cerr << "pair2.second: " << pair2.second.first << std::endl;
	// std::cerr << "pair2.second: " << pair2.second.second << std::endl;
	// if (pair1.first != pair2.first && pair1.first != pair2.second &&
    //        pair1.second != pair2.first && pair1.second != pair2.second) {
	// 		std::cerr << "herehreer\n";
	// 		exit(1);
	// 	   }

    // return pair1.first != pair2.first && pair1.first != pair2.second &&
        //    pair1.second != pair2.first && pair1.second != pair2.second;
	return (pair1.first != pair2.first && pair1.second != pair2.second) &&
           (pair1.first != pair2.second && pair1.second != pair2.first);
}

int RubiksCube::rank() const {
	int rank = 0;
	
	// std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> cornerPairs = {
    //     // CornerPair0 - ULB/URF
    //     {{'O', 'G'}, {'R', 'B'}},
    //     // CornerPair1 - DLF/DRB
    //     {{'O', 'B'}, {'R', 'G'}},
    //     // CornerPair2 - URB/ULF
    //     {{'G', 'R'}, {'B', 'O'}},
    //     // CornerPair3 - DLB/DRF
    //     {{'G', 'O'}, {'B', 'R'}}
    // };

	std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> cornerPairs = {
        // CornerPair0 - ULB/URF
		{{state[27], state[20]}, {state[9], state[2]}},
        // CornerPair1 - DLF/DRB
		{{state[35], state[6]}, {state[17], state[24]}},
        // CornerPair2 - UBR/UFL
		{{state[18], state[11]}, {state[0], state[29]}},
        // CornerPair3 - DLB/DRF
		{{state[8], state[15]}, {state[26], state[33]}},
    };

	// Rank among this many pairs.  For 8=8, 8C2->6C2->4C2->2C2 (28->15->6->1).
	std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> remaining = {
        {{'O', 'G'}, {'R', 'B'}},	//r
        {{'O', 'G'}, {'O', 'B'}},  // remove because ob
        {{'O', 'G'}, {'R', 'G'}}, //second
        {{'O', 'G'}, {'G', 'R'}},	//r
        {{'O', 'G'}, {'B', 'O'}},	//r
        {{'O', 'G'}, {'G', 'O'}},	//r
        {{'O', 'G'}, {'B', 'R'}},	//r

        {{'R', 'B'}, {'O', 'B'}}, //r
        {{'R', 'B'}, {'R', 'G'}}, //r
        {{'R', 'B'}, {'G', 'R'}}, 
        {{'R', 'B'}, {'B', 'O'}},
        {{'R', 'B'}, {'G', 'O'}}, //r
        {{'R', 'B'}, {'B', 'R'}},

        {{'O', 'B'}, {'R', 'G'}},
        {{'O', 'B'}, {'G', 'R'}},
        {{'O', 'B'}, {'B', 'O'}},		
        {{'O', 'B'}, {'G', 'O'}},		// first 16
        {{'O', 'B'}, {'B', 'R'}},

        {{'R', 'G'}, {'G', 'R'}},
        {{'R', 'G'}, {'B', 'O'}},
        {{'R', 'G'}, {'G', 'O'}},
        {{'R', 'G'}, {'B', 'R'}},

        {{'G', 'R'}, {'B', 'O'}},
        {{'G', 'R'}, {'G', 'O'}},
        {{'G', 'R'}, {'B', 'R'}},

        {{'B', 'O'}, {'G', 'O'}},
        {{'B', 'O'}, {'B', 'R'}},

        {{'G', 'O'}, {'B', 'R'}},
    };

	int bases[3];
	bases[2] = 1; // 2C2.

    for (int i = 1; i >= 0; --i) bases[i] = bases[i + 1] * choose((6) - 2*i, 2);

	unsigned numRemaining = 28;
	// std::cerr << "here\n";

	for (unsigned n = 0; n < 3; ++n) {
		// std::cerr << "gogo67\n";
		unsigned remainingInd = 0;
		// std::cerr << "gogo6\n";
		const auto& sPair = cornerPairs[n];
		// std::cerr << "gogo7\n";
		// std::cerr << "here2\n";
		std::cerr << "numRemaining: " << numRemaining << std::endl;
		std::cerr << "n: " << n << std::endl;

		for (unsigned r = 0; r < numRemaining; ++r) {
            const auto& rPair = remaining[r];

            // if (sPair == rPair) {
            if ((sPair.first == rPair.first && sPair.second == rPair.second) ||
					sPair.first == rPair.second && sPair.second == rPair.first) {
                rank += r * bases[n];
				std::cout << "rank: " << rank << std::endl;
				std::cout << "r: " << r << std::endl;
                break; // Found the match, stop searching
            }
        }

        std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> newRemaining;
        for (unsigned r = 0; r < numRemaining; ++r) {
            if (areDistinct(sPair, remaining[r])) {
				// std::cerr << "gogo1" << std::endl;
				// std::cerr << ""
                newRemaining.push_back(remaining[r]);
				// std::cerr << "gogo2" << std::endl;
            }
        }
		// std::cerr << "gogo3" << std::endl;
        remaining = newRemaining;
		// std::cerr << "gogo4" << std::endl;
        numRemaining = remaining.size();
		// std::cerr << "gogo5" << std::endl;
	}

	return rank;
}

// int RubiksCube::rank() const {
// 	int rank = 0;
	
// 	// std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> cornerPairs = {
//     //     // CornerPair0 - ULB/URF
//     //     {{'O', 'G'}, {'R', 'B'}},
//     //     // CornerPair1 - DLF/DRB
//     //     {{'O', 'B'}, {'R', 'G'}},
//     //     // CornerPair2 - URB/ULF
//     //     {{'G', 'R'}, {'B', 'O'}},
//     //     // CornerPair3 - DLB/DRF
//     //     {{'G', 'O'}, {'B', 'R'}}
//     // };

// 	std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> cornerPairs = {
//         // CornerPair0 - ULB/URF
// 		{{state[27], state[20]}, {state[9], state[2]}},
//         // CornerPair1 - DLF/DRB
// 		{{state[35], state[6]}, {state[17], state[24]}},
//         // CornerPair2 - UBR/UFL
// 		{{state[18], state[11]}, {state[0], state[29]}},
//         // CornerPair3 - DLB/DRF
// 		{{state[8], state[15]}, {state[26], state[33]}},
//     };

// 	// Rank among this many pairs.  For 8=8, 8C2->6C2->4C2->2C2 (28->15->6->1).
// 	std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> remaining = {
//         {{'O', 'G'}, {'R', 'B'}},
//         {{'O', 'G'}, {'O', 'B'}},
//         {{'O', 'G'}, {'R', 'G'}},
//         {{'O', 'G'}, {'G', 'R'}},
//         {{'O', 'G'}, {'B', 'O'}},
//         {{'O', 'G'}, {'G', 'O'}},
//         {{'O', 'G'}, {'B', 'R'}},

//         {{'R', 'B'}, {'O', 'B'}},
//         {{'R', 'B'}, {'R', 'G'}},
//         {{'R', 'B'}, {'G', 'R'}},
//         {{'R', 'B'}, {'B', 'O'}},
//         {{'R', 'B'}, {'G', 'O'}},
//         {{'R', 'B'}, {'B', 'R'}},

//         {{'O', 'B'}, {'R', 'G'}},
//         {{'O', 'B'}, {'G', 'R'}},
//         {{'O', 'B'}, {'B', 'O'}},
//         {{'O', 'B'}, {'G', 'O'}},
//         {{'O', 'B'}, {'B', 'R'}},

//         {{'R', 'G'}, {'G', 'R'}},
//         {{'R', 'G'}, {'B', 'O'}},
//         {{'R', 'G'}, {'G', 'O'}},
//         {{'R', 'G'}, {'B', 'R'}},

//         {{'G', 'R'}, {'B', 'O'}},
//         {{'G', 'R'}, {'G', 'O'}},
//         {{'G', 'R'}, {'B', 'R'}},

//         {{'B', 'O'}, {'G', 'O'}},
//         {{'B', 'O'}, {'B', 'R'}},

//         {{'G', 'O'}, {'B', 'R'}},
//     };

// 	int bases[3];
// 	bases[2] = 1; // 2C2.

//     for (int i = 1; i >= 0; --i) bases[i] = bases[i + 1] * choose((6) - 2*i, 2);

// 	unsigned numRemaining = 28;
// 	// std::cerr << "here\n";

// 	for (unsigned n = 0; n < 3; ++n)
// 	{
// 		unsigned remainingInd = 0;
// 		std::pair<std::pair<char, char>, std::pair<char, char>> sPair = cornerPairs[n];
// 		// std::cerr << "here2\n";
// 		// std::cerr << "numRemaining: " << numRemaining << std::endl;
// 		// std::cerr << "n: " << n << std::endl;

// 		for (unsigned r = 0; r < numRemaining; ++r)
// 		{
// 			std::pair<std::pair<char, char>, std::pair<char, char>> rPair = remaining[r];

// 			// std::cerr << "here33\n";
// 			if (sPair == rPair)
// 			{
// 				// Found the pair: rank it relative to the remaining pairs, and multiply
// 				// it by the base for digit n.
// 				rank += r * bases[n];
// 			}
//     		else if (areDistinct(sPair, rPair)) {
// 			// std::cerr << "here3\n";
// 			// The pair excludes the numbers in set[n], so keep it in the
// 			// list of remaining pairs for the next digit's rank.
// 				remaining[remainingInd++] = rPair;
// 			}
// 		}
// 		// Number of remaining pairs.
// 		numRemaining = remainingInd;
// 	}

// 	return rank;
// }

int RubiksCube::calculateStateIndexG2(const RubiksCube& cube) {
    int cornerIndex = cube.rank();
    // int cornerIndex = encodeCornerTetradG2(cube);
    int edgeIndex = encodeEdgeSlicePositionsG2(cube);
    std::vector<int> edgePermutation = cube.getEdgePermutationG2();
    int parity = cube.calculateParityG2(edgePermutation);  // Calculate parity from edge permutation

	std::cout << "cornerIndex: " << cornerIndex << std::endl;
	std::cout << "edgeIndex: " << edgeIndex << std::endl;
	std::cout << "parity: " << parity << std::endl;
	// int stateIndex = (cornerIndex * 70 + edgeIndex) * 2 + parity;
	return (edgeIndex * 2520 + cornerIndex) * 2 + parity;
    // return stateIndex;
}

// int RubiksCube::calculateStateIndexG2(const RubiksCube& cube) {
//     int cornerIndex = encodeCornerTetradG2(cube);
//     int edgeIndex = encodeEdgeSlicePositionsG2(cube);
//     // int parity = cube.calculateParityG2(cube.getCornerPermutationG2());
// 	// std::cout << "corner index = " << cornerIndex << std::endl;
// 	// std::cout << "edgeIndex = " << edgeIndex << std::endl;
// 	// std::cout << "cornerIndex * 495 + edgeIndex = " << cornerIndex * 495 + edgeIndex << std::endl;
// 	// std::cout << "cornerIndex: " << cornerIndex << std::endl;
// 	// std::cout << "cornerIndex: " << cornerIndex << std::endl;
//     // return cornerIndex;
// 	// if (cornerIndex * 495 + edgeIndex == 5)
// 	// 	std::cout << "hello im " << cornerIndex * 495 + edgeIndex << std::endl;
// 	// int offset = (parity == 1) ? 352800 : 0;
//     return cornerIndex * 70 + edgeIndex;
// 	// return offset + (cornerIndex * 70 + edgeIndex);
//     // return edgeIndex;
// }

void RubiksCube::calculateCornerTetradIndex() const {
	// const std::vector<std::vector<int>> tetrads = {
    //     {1, 3, 5, 7},  // Tetrad 1
    //     {0, 2, 4, 6}   // Tetrad 2
    // };
	const std::vector<std::set<char>> firstTetradColors = {
		{'Y', 'G', 'R'}, {'Y', 'B', 'O'}, {'W', 'B', 'R'}, {'W', 'G', 'O'}
	};
	const std::vector<std::set<char>> secondTetradColors = {
		{'Y', 'O', 'G'}, {'Y', 'R', 'B'}, {'W', 'O', 'B'}, {'W', 'R', 'G'}
	};
	for (int i = 0; i < CORNER_COUNT; i++) {
        char color1 = state[cornerIndices[i][0]];
        char color2 = state[cornerIndices[i][1]];
        char color3 = state[cornerIndices[i][2]];

		std::set<char> cornerColors = {color1, color2, color3};

		for (auto& firstTetrad : firstTetradColors) {
			if (firstTetrad == cornerColors) {
				std::cout << "Corner " << i << " is in T1";
				if (i % 2 != 0) {
                        std::cout << "\x1B[32m (good)\x1B[0m" << std::endl;
                    } else {
                        std::cout << "\x1B[31m (bad)\x1B[0m" << std::endl;
                    }
			}
		}
		for (auto& secondTetrad : secondTetradColors) {
			if (secondTetrad == cornerColors) {
				std::cout << "Corner " << i << " is in T2";
				if (i % 2 == 0) {
                    std::cout << "\x1B[32m (good)\x1B[0m" << std::endl;
                } else {
                    std::cout << "\x1B[31m (bad)\x1B[0m" << std::endl;
                }
				break;
			}
		}
    }
}

void RubiksCube::IsCornerInCorrectTetrad(const RubiksCube& cube) {
	cube.calculateCornerTetradIndex();
}

// void RubiksCube::CalculateCycles() {
// 	for (int i = 0; i < 11; i++) {
// 		char color1 = state[edgeIndices[i][0]];
//     	char color2 = state[edgeIndices[i][1]];
// 		std::pair colors = {color1, color2};
// 		auto it = std::find(edgesBaseColours.begin(), edgesBaseColours.end(), colors);
//         if (it != edgesBaseColours.end()) {
//             int intendedIndex = std::distance(edgesBaseColours.begin(), it);
// 			i = in
//             std::cout << "Edge number: " << i << " wants to go to edge position: " << intendedIndex << std::endl;
//         } else {
//             std::cout << "Edge number: " << i << " does not have a matching base color in edgesBaseColours." << std::endl;
//         }
// 	}
// }

void RubiksCube::CalculateCycles() {
        std::map<std::pair<char, char>, std::string> edgeNames = {
            {{'W', 'B'}, "WB"}, {{'W', 'G'}, "WG"},
            {{'Y', 'G'}, "YG"}, {{'Y', 'R'}, "YR"},
            {{'Y', 'B'}, "YB"}, {{'Y', 'O'}, "YO"},
            {{'W', 'R'}, "WR"}, {{'W', 'O'}, "WO"},
            {{'B', 'R'}, "BR"}, {{'B', 'O'}, "BO"},
            {{'G', 'R'}, "GR"}, {{'G', 'O'}, "GO"}
        };

        std::vector<bool> visited(12, false); // Track visited edges
        std::vector<int> cycle;
        int cycleCount = 1;

        for (int i = 0; i < 12; i++) {
            if (!visited[i]) {
                cycle.clear();
                int current = i;

                // Follow the cycle starting from the current edge
                while (!visited[current]) {
                    visited[current] = true;
                    cycle.push_back(current);

                    char color1 = state[edgeIndices[current][0]];
                    char color2 = state[edgeIndices[current][1]];
                    std::pair<char, char> colors = {color1, color2};

                    // Find this pair in the base colors list to determine its intended position
                    auto it = std::find(edgesBaseColours.begin(), edgesBaseColours.end(), colors);
                    if (it != edgesBaseColours.end()) {
                        current = std::distance(edgesBaseColours.begin(), it);
                    } else {
                        std::cerr << "Edge number: " << current << " does not have a matching base color." << std::endl;
                        break;
                    }
                }

                // Output the cycle
                if (!cycle.empty()) {
                    std::cout << "Cycle " << cycleCount << ": ";
                    for (size_t idx = 0; idx < cycle.size(); ++idx) {
                        int pos = cycle[idx];
                        char color1 = state[edgeIndices[pos][0]];
                        char color2 = state[edgeIndices[pos][1]];
                        std::pair<char, char> colors = {color1, color2};

                        std::cout << edgeNames[colors];
                        if (idx < cycle.size() - 1) {
                            std::cout << " wants to go to ";
                        }
                    }
                    std::cout << "." << std::endl;
                    cycleCount++;
                }
            }
        }
    }