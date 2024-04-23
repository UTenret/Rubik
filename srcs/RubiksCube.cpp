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

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
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

// bool RubiksCube::isEdgeInESliceG1(int edgeIndex) const {
//     const auto& indices = edgeIndices[edgeIndex];
//     char color1 = state[indices[0]]; // one side of the edge
//     char color2 = state[indices[1]]; // other side of the edge

//     // Assuming colors not on the U or D face are in the E slice
//     // Define colors that belong to U or D layers
//     std::set<char> uOrDColors = {'W', 'Y'}; // Adjust according to your cube's color scheme

// 	std::cout << "edgeIndex: " << edgeIndex << std::endl;
// 	std::cout << "color1: " << color1 << std::endl;
// 	std::cout << "color2: " << color2 << std::endl;
//     return uOrDColors.find(color1) == uOrDColors.end() && uOrDColors.find(color2) == uOrDColors.end();
// }

bool RubiksCube::isEdgeInESliceG1(int edgeIndex) const {
    // Set of edge positions expected to be in the E slice.
    // Assuming FL, FR, BL, BR are indexed as such in the EdgePositions enum and represent middle slice positions.
    // std::set<int> eSliceIndices = {FL, FR, BL, BR};  // Correct indices for the E slice edges

    // // Ensure the edge index is one that should be in the E slice.
    // if (eSliceIndices.find(edgeIndex) == eSliceIndices.end()) {
    //     return false;  // This edge is not one of the designated middle slice edges.
    // }


	// we pass index of the edge were looking for like 0 is 37, 19 OR UB OR YELLOW/GREEN
	// so we need also something that maps edges to their colours
	// we search the cube for the location of yellow green, if yellow green is one of the 
	// middle edges index, we return true otherwise we return false
	std::vector<std::pair<char, char>> middleColor;
	middleColor.push_back({state[5], state[12]});
	middleColor.push_back({state[3], state[32]});
	middleColor.push_back({state[21], state[14]});
	middleColor.push_back({state[23], state[30]});

	// std::cout << "middleColor.first:" << middleColor[0].first << std::endl;
	// std::cout << "middleColor.second:" << middleColor[1].second << std::endl;
	// middleColor.push_back({edgesBaseColours[8]});
	// middleColor.push_back(edgesBaseColours[9]);
	// middleColor.push_back(edgesBaseColours[10]);
	// middleColor.push_back(edgesBaseColours[11]);

    std::pair<char, char> color = edgesBaseColours[edgeIndex];
	for (std::pair<char, char> pair : middleColor) {
		if (pair == color)  {
			// std::cout << "pair.first: " << pair.first <<  ", pair.second: " << pair.second <<std::endl;
			// std::cout << "color.first: " << color.first << ", color.second: " << color.second <<std::endl;
			return true;
		}
	}
	// return middleColor.find(color) != middleColor.end();
	return false;
}

int RubiksCube::encodeCornerOrientationsG1(const RubiksCube& cube) {
    int index = 0;
    int multiplier = 1;
    for (int i = 0; i < 7; i++) {  // Assuming the last corner's orientation is implicitly determined
        int orientation = cube.getCornerOrientationG1(i);
        index += orientation * multiplier;
        multiplier *= 3;
    }
    return index;
}

// int RubiksCube::encodeEdgeSlicePositionsG1(const RubiksCube& cube) {
//     int index = 0;
//     for (int i = 0; i < 12; i++) {  // Assume 12 edges, check if each is in E slice
//         if (cube.isEdgeInESliceG1(i)) {
// 			// std::cout << "edge: " << i << " is in ES slice\n";
//             index |= (1 << i);
//         }
//     }
//     return index;
// }

// int RubiksCube::encodeEdgeSlicePositionsG1(const RubiksCube& cube) {
//     std::vector<int> positions; // To hold positions of edges that are in the E slice
// 	std::cout << "||||||||||||||||||encodeEdgeSlicePositionsG1||||||||||||||\n";
// 	cube.printCube();
//     // for (int i = 0; i < 12; i++) {
//     //     if (cube.isEdgeInESliceG1(i)) {
// 	// 		std::cout << "this edge is in the middle: " << i << std::endl;
//     //         positions.push_back(i);
//     //     }
//     // }
// 	// for (int i = 8; i < 12; i++) positions.push_back(i);
// 	positions.push_back(0);
// 	positions.push_back(1);
// 	positions.push_back(2);
// 	positions.push_back(3);

//     // Now we need to encode these positions into a combinatorial index
//     // Assume positions are always sorted and exactly four are in the E slice
//     int index = 0, k = 4;
//     for (unsigned long i = 0; i < positions.size(); ++i) {
//         int pos = positions[i];
// 		std::cout << "pos: " << pos << std::endl;
//         // for (int j = 0; j < pos; ++j) {
//             // if (std::find(positions.begin(), positions.end(), j) == positions.end()) {
//                 // j is not in positions, it's a combination without this element
// 				std::cout << "i: " << i << std::endl;
// 				// std::cout << "j: " << j << std::endl;
// 				int bCoeff = binomialCoefficient(11 - pos, k - 1);
// 				if (bCoeff == 1) break;
//                 index += bCoeff;
// 				std::cout << "index: " << index << std::endl;
// 				// break;
//                 // index += binomialCoefficient(11 - j, k - 1);
//             // }
//         // }
// 		// k = 11 - pos == 4 ? k - 2 : k - 1;
//         k--;
//     }
// 	exit(1);
//     return index;
// }

int RubiksCube::encodeEdgeSlicePositionsG1(const RubiksCube& cube) {
    std::vector<int> positions;

	for (int i = 0; i < 12; i++) {
        if (cube.isEdgeInESliceG1(i)) {
			// std::cout << "this edge is in the middle: " << i << std::endl;
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
	return index;
	// std::cout << "index: " << index << std::endl;
	// exit(1);
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
    return cornerIndex * 495 + edgeIndex;
    // return edgeIndex;
}
