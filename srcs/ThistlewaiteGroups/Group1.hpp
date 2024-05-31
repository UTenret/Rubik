#pragma once

#include "RubiksCube.hpp"
#include <vector>
#include <string>

class Group1 {
public:
    static int getCornerOrientation(const RubiksCube& cube, int cornerIndex);
    static bool isEdgeInESlice(const RubiksCube& cube, int edgeIndex);
    static int encodeCornerOrientations(const RubiksCube& cube);
    static int encodeEdgeSlicePositions(const RubiksCube& cube);
    static int calculateStateIndex(const RubiksCube& cube);
    static const std::vector<std::string> moves;
};
