#include "PruningTable.hpp"

PruningTable::PruningTable(const RubiksCube& cube) : cube(cube), lut0(2048, -1) {}

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

    std::vector<std::string> moves = {"U", "U'", "D", "D'", "R", "R'", "L", "L'", "F", "F'", "B", "B'", "U2", "D2", "R2", "L2", "F2", "B2"};

    while (!q.empty()) {
        auto [currentCube, dist] = q.front();
        q.pop();

        std::string currentEdgeOrientation = RubiksCube::encodeEdgeOrientationsG0(currentCube.getState());
        int index = RubiksCube::calculateStateIndexG0(currentEdgeOrientation);

        if (lut0[index] == -1 || lut0[index] > dist) {
            lut0[index] = dist;
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

// No F, F', B, B' for G1->G2

void PruningTable::generateLUT() {
    bfsGenerateLUTG0();
    std::ofstream file("G0.txt");
    if (!file) {
        std::cerr << "Error: file could not be opened";
        exit(1);
    }
    for (int value : lut0) {
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

const std::vector<int>& PruningTable::getLUT(int lutNumber) const {
	if (lutNumber < 0 || lutNumber > 1) {
		std::cerr << "we need an error message here\n";
		exit(1);
	}
	switch(lutNumber) {
		case 0:
			return lut0;
			break;
		case 1:
			return lut1;
			break;
	}
	exit(1);
}
