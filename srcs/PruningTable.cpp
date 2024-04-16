#include "PruningTable.hpp"

PruningTable::PruningTable(const RubiksCube& cube) : cube(cube) {}

void PruningTable::bfsGenerateLUT() {
    std::queue<std::pair<std::string, int>> q;
    std::set<std::string> visited;
    q.push({initialState, 0});
    visited.insert(encodeEdgeOrientations(initialState));

    std::vector<std::string> moves = getValidMoves();

    while (!q.empty()) {
        auto [currentState, dist] = q.front();
        q.pop();

        std::string currentEdgeOrientation = encodeEdgeOrientations(currentState);
        int index = calculateStateIndex(currentEdgeOrientation);
        if (lut[index] == -1 || lut[index] > dist) {
            lut[index] = dist;
        }

        if (dist >= MAX_DEPTH) continue;

        for (const auto& move : moves) {
            std::string newState = currentState;
            cube.applyMove(newState, move); // Needs to be defined or available externally.

            std::string newEdgeOrientation = encodeEdgeOrientations(newState);
            if (visited.insert(newEdgeOrientation).second) {
                q.push({newState, dist + 1});
            }
        }
    }
}

void PruningTable::generateLUT(const std::string& filename) {
    bfsGenerateLUT();
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
    int index = 0;

    while (file >> distance && index < loadedLUT.size()) {
        loadedLUT[index++] = distance;
    }

    return loadedLUT;
}

bool PruningTable::isEdgeFlipped(std::pair<char, char> colors) {
		return (colors.second == 'Y' || colors.second == 'W' || 
				colors.first == 'O' || colors.first == 'R');
}
