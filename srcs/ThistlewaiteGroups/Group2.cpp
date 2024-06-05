#include "Group2.hpp"
#include "RubiksCube.hpp"
#include <set>
#include <vector>
#include <array>
#include <bitset>
#include <utility>

const std::vector<std::string> Group2::moves = {
    "U", "U'", "D", "D'", "R2", "L2", "F2", "B2"
};

bool Group2::areDistinct(const std::pair<std::pair<char, char>, std::pair<char, char>>& pair1,
                         const std::pair<std::pair<char, char>, std::pair<char, char>>& pair2) {
    return (pair1.first != pair2.first && pair1.second != pair2.second) &&
           (pair1.first != pair2.second && pair1.second != pair2.first);
}

int Group2::calculateCornerIndex(const std::string& state) {
    int rank = 0;
    
    std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> cornerPairs = {
        {{'O', 'G'}, {'R', 'B'}},
        {{'O', 'B'}, {'R', 'G'}},
        {{'G', 'R'}, {'B', 'O'}},
        {{'G', 'O'}, {'B', 'R'}}
    };

    std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> remaining = {
        {{state[27], state[20]}, {state[9], state[2]}},
        {{state[27], state[20]}, {state[35], state[6]}},
        {{state[27], state[20]}, {state[17], state[24]}},
        {{state[27], state[20]}, {state[18], state[11]}},
        {{state[27], state[20]}, {state[8], state[15]}},
        {{state[27], state[20]}, {state[26], state[33]}},
        {{state[27], state[20]}, {state[0], state[29]}},

        {{state[9], state[2]}, {state[35], state[6]}},
        {{state[9], state[2]}, {state[17], state[24]}},
        {{state[9], state[2]}, {state[18], state[11]}},
        {{state[9], state[2]}, {state[8], state[15]}},
        {{state[9], state[2]}, {state[26], state[33]}},
        {{state[9], state[2]}, {state[0], state[29]}},

        {{state[35], state[6]}, {state[17], state[24]}},
        {{state[35], state[6]}, {state[18], state[11]}},
        {{state[35], state[6]}, {state[8], state[15]}},
        {{state[35], state[6]}, {state[26], state[33]}},
        {{state[35], state[6]}, {state[0], state[29]}},

        {{state[17], state[24]}, {state[18], state[11]}},
        {{state[17], state[24]}, {state[8], state[15]}},
        {{state[17], state[24]}, {state[26], state[33]}},
        {{state[17], state[24]}, {state[0], state[29]}},

        {{state[18], state[11]}, {state[8], state[15]}},
        {{state[18], state[11]}, {state[26], state[33]}},
        {{state[18], state[11]}, {state[0], state[29]}},

        {{state[8], state[15]}, {state[26], state[33]}},
        {{state[8], state[15]}, {state[0], state[29]}},

        {{state[26], state[33]}, {state[0], state[29]}}
    };

    int bases[3];
    bases[2] = 1; // 2C2.

    for (int i = 1; i >= 0; --i) bases[i] = bases[i + 1] * choose((6) - 2*i, 2);

    unsigned numRemaining = 28;

    for (unsigned n = 0; n < 3; ++n) {
        const auto& sPair = cornerPairs[n];

        for (unsigned r = 0; r < numRemaining; ++r) {
            const auto& rPair = remaining[r];

            if ((sPair.first == rPair.first && sPair.second == rPair.second) ||
                (sPair.first == rPair.second && sPair.second == rPair.first)) {
                rank += r * bases[n];
                break;
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

int Group2::calculateParity(const std::vector<int>& permutation) {
	int parity = 0;
	for (unsigned long i = 0; i < permutation.size(); ++i) {
		for (unsigned long j = i + 1; j < permutation.size(); ++j) {
			parity ^= permutation[i] < permutation[j];
		}
	}
	return parity;
}

int Group2::calculateStateIndex(const RubiksCube& cube) {
    int cornerIndex = calculateCornerIndex(cube.getState());
    int edgeIndex = encodeEdgeSlicePositions(cube);

    std::array<int, 4> edgeCombo;
    unsigned edgeComboInd = 0;

    for (int i = 0; i < 8 && edgeComboInd < 4; ++i) {
        if (isEdgeBlueOrGreen(cube, i)) {
            edgeCombo[edgeComboInd++] = i;
        }
    }

    std::vector<int> cornerPermutation = getCornerPermutation(cube);
    int parity = Group2::calculateParity(cornerPermutation);
    return (edgeIndex * 2520 + cornerIndex) * 2 + parity;
}

int Group2::encodeEdgeSlicePositions(const RubiksCube& cube) {
    std::vector<int> positions;

    for (int i = 0; i < 8; i++) {
        if (isEdgeBlueOrGreen(cube, i)) {
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

std::vector<int> Group2::getCornerPermutation(const RubiksCube& cube) {
    std::vector<int> cornerPermutation(CORNER_COUNT);
    const std::string& state = cube.getState();
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

bool Group2::isEdgeBlueOrGreen(const RubiksCube& cube, int edgeIndex) {
    const std::set<char> validSliceColors = {'G', 'B'};

    char color = cube.getState()[edgeIndices[edgeIndex][1]];

    return validSliceColors.find(color) != validSliceColors.end();
}
