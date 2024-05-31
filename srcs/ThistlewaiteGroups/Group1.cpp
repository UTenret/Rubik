#include "Group1.hpp"
#include "RubiksCube.hpp"

// no F, F', B, B'
const std::vector<std::string> Group1::moves = {"U", "U'", "D", "D'", "R", "R'", "L", "L'", "F2", "B2"};

int Group1::getCornerOrientation(const RubiksCube& cube, int cornerIndex) {
    const auto& indices = cornerIndices[cornerIndex];
    char colorU = cube.state[indices[0]]; // top part
    char colorL = cube.state[indices[1]]; // left part
    char colorR = cube.state[indices[2]]; // right part

    if (colorU == 'W' || colorU == 'Y') {
        return 0; // No rotation needed
    } else if (colorL == 'W' || colorL == 'Y') {
        return 1; // 120 degrees rotation
    } else if (colorR == 'W' || colorR == 'Y') {
        return 2; // 240 degrees rotation
    }
    return -1;
}

bool Group1::isEdgeInESlice(const RubiksCube& cube, int edgeIndex) {
    const std::set<std::pair<char, char>> validMiddleSliceColors = {
        {'B', 'R'}, {'R', 'B'},
        {'B', 'O'}, {'O', 'B'},
        {'G', 'R'}, {'R', 'G'},
        {'G', 'O'}, {'O', 'G'}
    };

    char color1 = cube.state[edgeIndices[edgeIndex][0]];
    char color2 = cube.state[edgeIndices[edgeIndex][1]];

    std::pair<char, char> edgeColors = {color1, color2};
    std::pair<char, char> edgeColorsReversed = {color2, color1};

    return validMiddleSliceColors.find(edgeColors) != validMiddleSliceColors.end() ||
           validMiddleSliceColors.find(edgeColorsReversed) != validMiddleSliceColors.end();
}

int Group1::encodeCornerOrientations(const RubiksCube& cube) {
    int index = 0;
    int multiplier = 1;

    for (int i = 0; i < 7; i++) {
        int orientation = getCornerOrientation(cube, i);
        index += orientation * multiplier;
        multiplier *= 3;
    }

    return index;
}

int Group1::encodeEdgeSlicePositions(const RubiksCube& cube) {
    std::vector<int> positions;

    for (int i = 0; i < 12; i++) {
        if (isEdgeInESlice(cube, i)) {
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

int Group1::calculateStateIndex(const RubiksCube& cube) {
    int cornerIndex = encodeCornerOrientations(cube);
    int edgeIndex = encodeEdgeSlicePositions(cube);

    return cornerIndex * 495 + edgeIndex; // 495 = 11 choose 4
}
