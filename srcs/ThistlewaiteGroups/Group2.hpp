#pragma once

#include "RubiksCube.hpp"
#include <vector>
#include <string>

class Group2 {
public:
    static const std::vector<std::string> moves;

    static int calculateCornerIndex(const std::string& state);
    static int calculateStateIndex(const RubiksCube& cube);
    static int encodeEdgeSlicePositions(const RubiksCube& cube);
    static std::vector<int> getCornerPermutation(const RubiksCube& cube);
    static bool isEdgeBlueOrGreen(const RubiksCube& cube, int edgeIndex);
	static int calculateParity(const std::vector<int>& permutation);
private:
    static bool areDistinct(const std::pair<std::pair<char, char>, std::pair<char, char>>& pair1,
                            const std::pair<std::pair<char, char>, std::pair<char, char>>& pair2);
};
