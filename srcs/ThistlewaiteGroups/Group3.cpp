#include "Group3.hpp"
#include "RubiksCube.hpp"

const std::vector<std::string> Group3::moves = {
    "U2", "D2", "R2", "L2", "F2", "B2"
};

int Group3::calculateCornerIndex(std::string state) {
    std::array<uint8_t, 4> tetrad1;

    for (int i = 0; i < 4; i++) {
        std::pair<char, char> colorPair = {state[cornerIndicesG3[i][1]], state[cornerIndicesG3[i][2]]};
        int color = getCornerIndexFromColors(colorPair);
        tetrad1[i] = color;
    }

    std::pair<char, char> urbColors = {state[cornerIndicesG3[4][1]], state[cornerIndicesG3[4][2]]};

    int tetradRank = calculatePermutationIndex(tetrad1);
    return tetradRank * 4 + getCornerIndexFromColors(urbColors);
}

int Group3::calculateStateIndex(const RubiksCube& cube) {
    int edgeIndex = Group3::calculateEdgeIndex(cube.getState());
    int cornerIndex = Group3::calculateCornerIndex(cube.getState());

    return edgeIndex * 96 + cornerIndex;
}

int Group3::calculateEdgeIndex(std::string state) {
    std::array<uint8_t, 4> m;
    std::array<uint8_t, 4> s;
    std::array<uint8_t, 2> e;

    for (int i = 0; i < 10; i++) {
        std::pair<char, char> colorPair = {state[edgeIndicesG3[i][0]], state[edgeIndicesG3[i][1]]};
        int color = getEdgeIndexFromColors(colorPair);
        if (i < 4) m[i] = color;
        else if (i < 8) s[i - 4] = color;
        else e[i - 8] = color;
    }

    return calculatePermutationIndex(m) * 288 + calculatePermutationIndex(s) * 12 + calculatePartialPermutationIndex(e);
}

int Group3::calculatePermutationIndex(const std::array<uint8_t, 4>& perm) {
    std::array<uint32_t, (1 << 4) - 1> onesCountLookup;
    for (uint32_t i = 0; i < (1 << 4) - 1; ++i) {
        std::bitset<4> bits(i);
        onesCountLookup[i] = bits.count();
    }

    std::array<uint32_t, 4> lehmer;

    std::bitset<4> seen;
    lehmer[0] = perm[0];
    seen[4 - 1 - perm[0]] = 1;

    for (uint32_t i = 1; i < 4; ++i) {
        seen[4 - 1 - perm[i]] = 1;
        uint32_t numOnes = onesCountLookup[seen.to_ulong() >> (4 - perm[i])];
        lehmer[i] = perm[i] - numOnes;
    }

    uint32_t index = 0;
    for (uint32_t i = 0; i < 4; ++i) {
        index += lehmer[i] * pick(4 - 1 - i, 4 - 1 - i);
    }

    return index;
}

int Group3::calculatePartialPermutationIndex(const std::array<uint8_t, 2>& perm) {
    std::array<uint32_t, (1 << 4) - 1> onesCountLookup;
    for (uint32_t i = 0; i < (1 << 4) - 1; ++i) {
        std::bitset<4> bits(i);
        onesCountLookup[i] = bits.count();
    }

    std::array<uint32_t, 2> lehmer;

    std::bitset<4> seen;
    lehmer[0] = perm[0];
    seen[4 - 1 - perm[0]] = 1;

    for (uint32_t i = 1; i < 2; ++i) {
        seen[4 - 1 - perm[i]] = 1;
        uint32_t numOnes = onesCountLookup[seen.to_ulong() >> (4 - perm[i])];
        lehmer[i] = perm[i] - numOnes;
    }

    uint32_t index = 0;
    for (uint32_t i = 0; i < 2; ++i) {
        index += lehmer[i] * pick(4 - 1 - i, 2 - 1 - i);
    }

    return index;
}

int Group3::getCornerIndexFromColors(std::pair<char, char> corner) {
    if (corner.first == 'O' && corner.second == 'G') return 0;
    else if (corner.first == 'R' && corner.second == 'B') return 1;
    else if (corner.first == 'O' && corner.second == 'B') return 2;
    else if (corner.first == 'R' && corner.second == 'G') return 3;
    else if (corner.first == 'G' && corner.second == 'R') return 0;
    else if (corner.first == 'B' && corner.second == 'O') return 1;
    else if (corner.first == 'G' && corner.second == 'O') return 2;
    else if (corner.first == 'B' && corner.second == 'R') return 3;
    else return -1;
}

int Group3::getEdgeIndexFromColors(std::pair<char, char> edge) {
    if (edge.first == 'Y' && edge.second == 'G') return 0;
    else if (edge.first == 'Y' && edge.second == 'B') return 1;
    else if (edge.first == 'W' && edge.second == 'B') return 2;
    else if (edge.first == 'W' && edge.second == 'G') return 3;

    if (edge.first == 'Y' && edge.second == 'R') return 0;
    else if (edge.first == 'Y' && edge.second == 'O') return 1;
    else if (edge.first == 'W' && edge.second == 'O') return 2;
    else if (edge.first == 'W' && edge.second == 'R') return 3;

    if (edge.first == 'B' && edge.second == 'R') return 0;
    else if (edge.first == 'B' && edge.second == 'O') return 1;
    else if (edge.first == 'G' && edge.second == 'R') return 2;
    else if (edge.first == 'G' && edge.second == 'O') return 3;

    std::cerr << "Fatal error: invalid edge colors\n";
    exit(1);
    return -1;
}
