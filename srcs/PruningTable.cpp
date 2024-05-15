#include "PruningTable.hpp"

// PruningTable::PruningTable(const RubiksCube& cube) : cube(cube), lut0(2048, -1), lut1(2187, -1) {}
// PruningTable::PruningTable(const RubiksCube& cube) : cube(cube), luts[0](2048, -1), luts[1](1082565, -1) {}
PruningTable::PruningTable(const RubiksCube& cube) : cube(cube), luts(3) {}

/*
the queue holds cube state as a string and the distance to solved
visited holds the edges orientations because we dont care about anything else for G0->G1

*/

void PruningTable::bfsGenerateLUTG0() {
    std::queue<std::pair<RubiksCube, int>> q;
    std::set<std::string> visited;
    RubiksCube initialCube = cube;
    std::string initialEdgeOrientation = RubiksCube::encodeEdgeOrientationsG0(initialCube.getState());
    q.push({initialCube, 0});
    visited.insert(initialEdgeOrientation);
	luts[0].resize(2048, -1);  //change that, init somewhere else

    // std::vector<std::string> moves = {"U", "U'", "D", "D'", "R", "R'", "L", "L'", "F", "F'", "B", "B'", "U2", "D2", "R2", "L2", "F2", "B2"};
	const std::vector<std::string> moves = {
    	"U", "U'", "F", "F'", "R", "R'", "D", "D'", "L", "L'", "B", "B'",
	};
    while (!q.empty()) {
        auto [currentCube, dist] = q.front();
        q.pop();

        std::string currentEdgeOrientation = RubiksCube::encodeEdgeOrientationsG0(currentCube.getState());
        int index = RubiksCube::calculateStateIndexG0(currentEdgeOrientation);

        if (luts[0][index] == -1 || luts[0][index] > dist) {
            luts[0][index] = dist;
        }

        if (dist >= MAX_DEPTH) continue;

        for (const auto& move : moves) {
            RubiksCube newStateCube = currentCube;
            newStateCube.applyMove(move);

            std::string newEdgeOrientation = RubiksCube::encodeEdgeOrientationsG0(newStateCube.getState());
            if (visited.insert(newEdgeOrientation).second) {
                q.push({newStateCube, dist + 1});
            }
        }
    }
}

void PruningTable::bfsGenerateLUTG1() {
    std::queue<std::pair<RubiksCube, int>> q;
    std::set<int> visitedIndices;
    RubiksCube initialCube = cube;
	luts[1].resize(1082565, -1);
    int initialIndex = RubiksCube::calculateStateIndexG1(initialCube);
    q.push({initialCube, 0});
    visitedIndices.insert(initialIndex);

    std::vector<std::string> moves = {"U", "U'", "D", "D'", "R", "R'", "L", "L'", "F2", "B2"};
    // std::vector<std::string> moves = {"U", "L", "R"};

		// cube.printCube();
    while (!q.empty()) {
        auto [currentCube, dist] = q.front();
        q.pop();

        int currentIndex = RubiksCube::calculateStateIndexG1(currentCube);
        // if (luts[1][currentIndex] == -1 || luts[1][currentIndex] > dist) {
        if (luts[1][currentIndex] == -1 || luts[1][currentIndex] < dist) {
			// std::cout << "added index: " << currentIndex << " with dist: " << dist << std::endl;
            luts[1][currentIndex] = dist;
        }

        if (dist >= MAX_DEPTH)  {
			std::cout << "dist: "<< dist << std::endl;
			continue;
		}

        for (const auto& move : moves) {
            RubiksCube newStateCube = currentCube;
            newStateCube.applyMove(move);

            int newIndex = RubiksCube::calculateStateIndexG1(newStateCube);

			// std::cout << "dist: " << dist << ", move: " << move << ", state: " << newIndex << std::endl;
			// std::cout << "move: " << move << std::endl;
			// std::cout << "state: " << newIndex << std::endl;

            if (visitedIndices.insert(newIndex).second) {
				// std::cout << "added state: " << newIndex << " to visited\n";
                q.push({newStateCube, dist + 1});
            }
        }
    }
}

void PruningTable::bfsGenerateLUTG2() {
    std::queue<std::tuple<RubiksCube, int, std::vector<std::string>>> q;
    std::set<int> visitedIndices;
    RubiksCube initialCube = cube;
    luts[2].resize(352800, -1);
    int initialIndex = RubiksCube::calculateStateIndexG2(initialCube);
    q.push(std::make_tuple(initialCube, 0, std::vector<std::string>()));
    visitedIndices.insert(initialIndex);

    std::vector<std::string> moves = {"U", "U'", "D", "D'", "R2", "L2", "F2", "B2"};

    while (!q.empty()) {
        auto [currentCube, dist, path] = q.front();
        q.pop();

        int currentIndex = RubiksCube::calculateStateIndexG2(currentCube);

        if (luts[2][currentIndex] == -1 || luts[2][currentIndex] < dist) {
            luts[2][currentIndex] = dist;
        }

        if (dist >= MAX_DEPTH) {
            std::cout << "Reached max depth at index: " << currentIndex << " with distance: " << dist << std::endl;
            continue;
        }

        for (const auto& move : moves) {
            RubiksCube newStateCube = currentCube;
            newStateCube.applyMove(move);

            int newIndex = RubiksCube::calculateStateIndexG2(newStateCube);
            std::vector<std::string> newPath = path;
            newPath.push_back(move);

            if (visitedIndices.insert(newIndex).second) {
                q.push(std::make_tuple(newStateCube, dist + 1, newPath));

                // Check if the newIndex is one of the indices of interest
                if (newIndex == 7216) {
                    std::cout << "Reached target index " << newIndex << " with moves: ";
					RubiksCube::encodeEdgeSlicePositionsG2Debug(newStateCube);
                    for (const auto& m : newPath) {
                        std::cout << m << " ";
                    }
					newStateCube.printCube();
                    std::cout << std::endl;
                    // Optionally, you can save this path somewhere if needed
                }
            }
        }
    }
}

// void PruningTable::bfsGenerateLUTG2() {
//     std::queue<std::pair<RubiksCube, int>> q;
//     std::set<int> visitedIndices;
//     RubiksCube initialCube = cube;
// 	luts[2].resize(352800, -1);
//     int initialIndex = RubiksCube::calculateStateIndexG2(initialCube);
//     q.push({initialCube, 0});
//     visitedIndices.insert(initialIndex);

//     std::vector<std::string> moves = {"U", "U'", "D", "D'", "R2", "L2", "F2", "B2"};

// 		// cube.printCube();
//     while (!q.empty()) {
//         auto [currentCube, dist] = q.front();
//         q.pop();

//         int currentIndex = RubiksCube::calculateStateIndexG2(currentCube);
//         // if (luts[1][currentIndex] == -1 || luts[1][currentIndex] > dist) {
//         if (luts[2][currentIndex] == -1 || luts[2][currentIndex] < dist) {
// 			// std::cout << "added index: " << currentIndex << " with dist: " << dist << std::endl;
//             luts[2][currentIndex] = dist;
//         }

//         if (dist >= MAX_DEPTH)  {
// 			std::cout << "dist: "<< dist << std::endl;
// 			continue;
// 		}

//         for (const auto& move : moves) {
//             RubiksCube newStateCube = currentCube;
//             newStateCube.applyMove(move);

//             int newIndex = RubiksCube::calculateStateIndexG2(newStateCube);

// 			// std::cout << "dist: " << dist << ", move: " << move << ", state: " << newIndex << std::endl;
// 			// std::cout << "move: " << move << std::endl;
// 			// std::cout << "state: " << newIndex << std::endl;

//             if (visitedIndices.insert(newIndex).second) {
// 				// std::cout << "added state: " << newIndex << " to visited\n";
//                 q.push({newStateCube, dist + 1});
//             }
//         }
//     }
// }

// No F, F', B, B' for G1->G2

void PruningTable::generateLUT() {
    bfsGenerateLUTG0();
    // bfsGenerateLUTG1();
    bfsGenerateLUTG2();
    std::ofstream file("G0.txt");
    // std::ofstream file2("G1.txt");
    std::ofstream file3("G2.txt");
    if (!file ) {
        std::cerr << "Error: file could not be opened";
        exit(1);
    }
    for (int value : luts[0]) {
        file << value << std::endl;
    }
	// for (int value : luts[1]) {
	// 	file2 << value << std::endl;
	// }
	for (int value : luts[2]) {
		file3 << value << std::endl;
	}
}

std::vector<int> PruningTable::loadLUT(const std::string& filename, int size) {
    std::ifstream file(filename);
    int distance;
    std::vector<int> loadedLUT(size, -1);
    unsigned long index = 0;

    while (file >> distance && index < loadedLUT.size()) {
        loadedLUT[index++] = distance;
    }

    return loadedLUT;
}

const std::vector<int>& PruningTable::getLUT(int lutNumber) const {
	if (lutNumber < 0 || lutNumber > 2) {
		std::cerr << "we need an error message here\n";
		exit(1);
	}
	switch(lutNumber) {
		case 0:
			return luts[0];
			break;
		case 1:
			return luts[1];
			break;
		case 2:
			return luts[2];
			break;
	}
	exit(1);
}

void PruningTable::setLUT(int lutNumber, const std::vector<int>& lutData) {
    if (lutNumber < 0 || lutNumber > luts.size()) {
        throw std::out_of_range("LUT number out of range.");
    }
    if (lutNumber >= luts.size()) {
        luts.resize(lutNumber + 1);
    }
    luts[lutNumber] = lutData;
}
