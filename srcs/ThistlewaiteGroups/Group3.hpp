#pragma once

#include "RubiksCube.hpp"
#include <vector>
#include <string>

class Group3 {
    public:
        static int calculateStateIndex(const RubiksCube& cube);
        static int calculateCornerIndex(std::string state);
        static int calculateEdgeIndex(std::string state);
        static int calculatePartialPermutationIndex(const std::array<uint8_t, 2>& perm);
        static int calculatePermutationIndex(const std::array<uint8_t, 4>& perm);
        static int getCornerIndexFromColors(std::pair<char, char> corner);
        static int getEdgeIndexFromColors(std::pair<char, char> edge);
        static const std::vector<std::string> moves;
};
