#pragma once

#include "RubiksCube.hpp"
#include <vector>
#include <string>

class Group0 {
public:
    static std::string encodeEdgeOrientations(const RubiksCube& cube);
    static int calculateStateIndex(const RubiksCube& cube);
    static bool isEdgeFlipped(std::pair<char, char> colors);
    static const std::vector<std::string> moves;
};
