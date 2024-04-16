#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <cstring>
#include "RubiksCube.hpp"

enum EdgePositions {
	UB, UR, UF, UL,
	DR, DF, DL, DB,
	FR, FL, BR, BL,
	EDGE_COUNT
};

const int edgeIndices[EDGE_COUNT][2] = {
	{37, 19},	// UB || YG
	{41, 10},	// UR || YR
	{43, 1},	// UF || YB
	{39, 28},	// UL || YO

	{50, 16},	// DR || WR
	{46, 7},	// DF || WB
	{48, 34},	// DL || WO
	{52, 25},	// DB || WG

	{5,  12},	// FR || BR
	{3,  32},	// FL || BO
	{21, 14},	// BR || GR
	{23, 30},	// BL || GO
};

#define MAX_DEPTH 9

class PruningTable {
public:
    explicit PruningTable(const RubiksCube& cube);

    void generateLUT(const std::string& filename);
    std::vector<int> loadLUT(const std::string& filename);
    void solveCube(std::string& cube, const std::vector<int>& lut);

private:
	RubiksCube cube;
    std::vector<int> lut;

    void bfsGenerateLUT();
    bool isEdgeFlipped(const std::pair<char, char>& colors) const;
    int calculateStateIndex(const std::string& edgeOrientation) const;
    std::string encodeEdgeOrientations(const std::string& cube) const;
    std::vector<std::string> getValidMoves() const;
	bool isEdgeFlipped(std::pair<char, char> colors);
};
