#include "RubiksCube.hpp"
#include "Solver.hpp"

/*
 U
LFR
 D
 B
*/

std::vector<std::string> splitString(const std::string& str, char delimiter = ' ') {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

int main(int argc, char* argv[]) {
    // char cube[54] = {
    //     'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', // 0,  1,  2,  3   4,  5,  6,  7,  8		FRONT
    //     'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', // 9,  10, 11, 12, 13, 14, 15, 16, 17		RIGHT
    //     'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', // 18, 19, 20, 21, 22, 23, 24, 25, 26		BACK
    //     'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', // 27, 28, 29, 30, 31, 32, 33, 34, 35		LEFT
    //     'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', // 36, 37, 38, 39, 40, 41, 42, 43, 44		UP
    //     'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'	//  45, 46, 47, 48, 49, 50, 51, 52, 53		DOWN
    // };

	std::string initialState = 
    "BBBBBBBBB"  // FRONT: 0 - 8
    "RRRRRRRRR"  // RIGHT: 9 - 17
    "GGGGGGGGG"  // BACK: 18 - 26
    "OOOOOOOOO"  // LEFT: 27 - 35
    "YYYYYYYYY"  // UP: 36 - 44
    "WWWWWWWWW"; // DOWN: 45 - 53

	RubiksCube		cube(initialState);
	// RubiksCube		cube(testState);
	PruningTable	table(cube); // keep this shit here we need the initial state to make the LUTs
	if (argc > 2)
		table.generateLUT();
	// std::cout << "state: " << cube.getState() << std::endl;
	// std::cout << "index: " << RubiksCube::encodeEdgeSlicePositionsG1(cube) << std::endl;
	// exit(1);
	if (argc > 1) {
		std::string scramble = argv[1];
		cube.scramble(argv[1]);
		cube.printCube();
	}
	else {
		std::cout << "Please input a scramble\n";
		return 1;
	}
	// std::cout << "state: " << cube.getState() << std::endl;
	// std::cout << "index: " << RubiksCube::encodeEdgeSlicePositionsG1(cube) << std::endl;
	// exit(1);

	// RubiksCube::calculateStateIndexG2(cube);
	// std::cout << "Size: " << UniqueEdgeIndex.size() << std::endl;
	// for (int x : UniqueEdgeIndex) {
	// 	std::cout << " Number: " << x;
	// }
	// std::cout << std::endl;
	 for (const auto& [cornerIndex, edgeIndices] : cornerToEdgeIndexMap) {
        // std::cout << "Corner index " << cornerIndex << " has edge indices: ";
        // for (const auto& edgeIndex : edgeIndices) {
        //     std::cout << edgeIndex << " ";
        // }
        // std::cout << std::endl;

        // Check for missing edge indices
        for (int i = 0; i < 70; ++i) {
            if (edgeIndices.find(i) == edgeIndices.end()) {
        		std::cout << "Missing edge indices for corner index " << cornerIndex << ": ";
                std::cout << i << " " << std::endl;
            }
        }
    }
	for (const auto& [edgeIndex, cornerIndices] : edgeToCornerIndexMap) {
        // std::cout << "Corner index " << cornerIndex << " has edge indices: ";
        // for (const auto& edgeIndex : edgeIndices) {
        //     std::cout << edgeIndex << " ";
        // }
        // std::cout << std::endl;

        // Check for missing edge indices
        for (int i = 0; i < 2520; ++i) {
            if (cornerIndices.find(i) == cornerIndices.end()) {
        		std::cout << "Missing corner indices for edge index " << edgeIndex << ": ";
                std::cout << i << ", rank without parity: " << (edgeIndex * 2520 + i) * 2 << std::endl;
            }
        }
    }
	for (const auto& [cornerEdgePair, parities] : cornerEdgeToParityMap) {
        auto [cornerIndex, edgeIndex] = cornerEdgePair;
        if (parities.size() < 2) {
            std::cout << "Missing parity for corner index " << cornerIndex << " and edge index " << edgeIndex << ": ";
            if (parities.find(0) == parities.end()) {
                std::cout << "0 ";
            }
            if (parities.find(1) == parities.end()) {
                std::cout << "1 ";
            }
            std::cout << std::endl;
        }
    }
	std::cout << "SIze: " << cornerToEdgeIndexMap.size() <<  std::endl;
	// exit(1);
	Solver			solver(cube, table);
	solver.solveCube();

    return 0;
}
