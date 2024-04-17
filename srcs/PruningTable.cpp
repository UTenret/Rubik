#include "PruningTable.hpp"

PruningTable::PruningTable(const RubiksCube& cube) : cube(cube), lut(2048, -1) {}

/*
the queue holds cube state as a string and the distance to solved
visited holds the edges orientations because we dont care about anything else for G0->G1

*/

void PruningTable::bfsGenerateLUTG0() {
    std::queue<std::pair<RubiksCube, int>> q;
    std::set<std::string> visited;
    RubiksCube initialCube = cube;  // Copy the initial state of the cube
    std::string initialEdgeOrientation = RubiksCube::encodeEdgeOrientationsG0(initialCube.getState());
    q.push({initialCube, 0});
    visited.insert(initialEdgeOrientation);

    std::vector<std::string> moves = {"U", "U'", "D", "D'", "R", "R'", "L", "L'", "F", "F'", "B", "B'", "U2", "D2", "R2", "L2", "F2", "B2"};

    while (!q.empty()) {
        auto [currentCube, dist] = q.front();
        q.pop();

        std::string currentEdgeOrientation = RubiksCube::encodeEdgeOrientationsG0(currentCube.getState());
        int index = RubiksCube::calculateStateIndexG0(currentEdgeOrientation);

        if (lut[index] == -1 || lut[index] > dist) {
            lut[index] = dist;
        }

        if (dist >= MAX_DEPTH) continue;

        for (const auto& move : moves) {
            RubiksCube newStateCube = currentCube;  // Make a copy of the current cube state
            newStateCube.applyMove(move);  // Apply move to the new cube state

            std::string newEdgeOrientation = RubiksCube::encodeEdgeOrientationsG0(newStateCube.getState());
            if (visited.insert(newEdgeOrientation).second) {
                q.push({newStateCube, dist + 1});
            }
        }
    }
}


// void PruningTable::bfsGenerateLUTG0() {
//     std::queue<std::pair<std::string, int>> q;
//     std::set<std::string> visited;
//     q.push({cube.getState(), 0});
//     visited.insert(cube.encodeEdgeOrientationsG0(cube.getState()));

// 	std::vector<std::string> moves = {"U", "U'", "D", "D'", "R", "R'", "L", "L'", "F", "F'", "B", "B'", "U2", "D2", "R2", "L2", "F2", "B2"};
// 	std::cerr << "here\n";
//     while (!q.empty()) {
//         auto [currentState, dist] = q.front();
//         q.pop();

//         std::string currentEdgeOrientation = cube.encodeEdgeOrientationsG0(currentState);
// 		std::cerr << "currentEdgeOrientation: "  << currentEdgeOrientation << "\n"; 
//         int index = cube.calculateStateIndexG0(currentEdgeOrientation);

//         if (lut[index] == -1 || lut[index] > dist) {
//             lut[index] = dist;
//         }

//         if (dist >= MAX_DEPTH) continue;

//         for (const auto& move : moves) {
//             std::string newState = currentState;
//             cube.applyMove(move);

//             std::string newEdgeOrientation = cube.encodeEdgeOrientationsG0(newState);
// 			std::cerr << "newEdgeOrientation: "  << newEdgeOrientation << "\n"; 
//             if (visited.insert(newEdgeOrientation).second) {
//                 q.push({newState, dist + 1});
//             }
//         }
//     }
// }

void PruningTable::generateLUT(const std::string& filename) {
    bfsGenerateLUTG0();
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: file could not be opened";
        exit(1);
    }
    for (int value : lut) {
        file << value << std::endl;
    }
}

std::vector<int> PruningTable::loadLUT(const std::string& filename) {
    std::ifstream file(filename);
    int distance;
    std::vector<int> loadedLUT(2048, -1);
    unsigned long index = 0;

    while (file >> distance && index < loadedLUT.size()) {
        loadedLUT[index++] = distance;
    }

    return loadedLUT;
}

const std::vector<int>& PruningTable::getLUT() const {
    return lut;
}