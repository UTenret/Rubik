#include "Group0.hpp"
#include "RubiksCube.hpp"

// We use all the moves for the G0-G1 transition
const std::vector<std::string> Group0::moves = {"U", "U'", "F", "F'", "R", "R'", "D", "D'", "L", "L'", "B", "B'"};

std::string Group0::encodeEdgeOrientations(const RubiksCube& cube) {
    std::string orientation;
    orientation.reserve(EDGE_COUNT);

    for (int i = 0; i < EDGE_COUNT; ++i) {
        std::pair<char, char> edgeColors = {cube.state[edgeIndices[i][0]], cube.state[edgeIndices[i][1]]};
        bool flipped = isEdgeFlipped(edgeColors);

        if (flipped) {
            orientation.push_back('1'); // Edge is flipped
        } else {
            orientation.push_back('0'); // Edge is not flipped
        }
    }

    return orientation;
}

int Group0::calculateStateIndex(const RubiksCube& cube) {
    std::string edgeOrientation = encodeEdgeOrientations(cube);
    int index = 0;
    for (size_t i = 0; i < edgeOrientation.size() - 1; ++i) {
        if (edgeOrientation[i] == '1') {
            index += (1 << i);
        }
    }
    return index;
}

bool Group0::isEdgeFlipped(std::pair<char, char> colors) {
    return (colors.second == 'Y' || colors.second == 'W' ||
            colors.first == 'O' || colors.first == 'R');
}