#pragma once

#include "RubiksCube.hpp"
#include <vector>
#include <string>

class Group0 {
public:
    static std::string encodeEdgeOrientationsG0(const RubiksCube& cube);
    static int calculateStateIndexG0(const RubiksCube& cube);
    static bool isEdgeFlippedG0(std::pair<char, char> colors);
    static const std::vector<std::string> moves;
};
