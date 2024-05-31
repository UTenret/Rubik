#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <set>
#include <cmath>
#include <queue>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <tuple>
#include <map>
#include <array>
#include <bitset>
#include "math.hpp"

constexpr int EDGE_COUNT = 12;
constexpr int CORNER_COUNT = 8;
constexpr int MAX_DEPTH = 16;
constexpr int G0_N_SOLUTIONS = 2048;
constexpr int G1_N_SOLUTIONS = 1082565;
constexpr int G2_N_SOLUTIONS = 352800;
constexpr int G3_N_SOLUTIONS = 663552;

enum EdgePositions {
	UB, UR, UF, UL,
	DR, DF, DL, DB,
	FR, FL, BR, BL
};

enum CornerPositions {
    UBL, UBR, UFR, UFL,
    DBL, DBR, DFR, DFL
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

const int edgeIndicesG3[EDGE_COUNT][2] = {
	{37, 19},	// UB || YG
	{43, 1},	// UF || YB
	{46, 7},	// DF || WB
	{52, 25},	// DB || WG
	
	{41, 10},	// UR || YR
	{39, 28},	// UL || YO
	{48, 34},	// DL || WO
	{50, 16},	// DR || WR

	{5,  12},	// FR || BR
	{3,  32},	// FL || BO
	{21, 14},	// BR || GR
	{23, 30},	// BL || GO
};

const int cornerIndicesG3[CORNER_COUNT][3] = {
    {36, 27, 20},		// YOG || ULB			//T 2
    {44, 9, 2},			// YRB || URF			//T 2
    {45, 35, 6},		// WOB || DLF			//T 2
    {53, 17, 24},		// WRG || DRB			//T 2

    {38, 18, 11},		// YGR || UBR			//T 1
    {42, 0, 29},		// YBO || UFL			//T 1
    {51, 26, 33},		// WGO || DBL			//T 1
    {47, 8, 15},		// WBR || DFR			//T 1
};

const std::vector<std::pair<char, char>> edgesBaseColours = {
    {'Y', 'G'}, // UB || Yellow-Green		0
    {'Y', 'R'}, // UR || Yellow-Red			1
    {'Y', 'B'}, // UF || Yellow-Blue		2
    {'Y', 'O'}, // UL || Yellow-Orange		3
    {'W', 'R'}, // DR || White-Red			4
    {'W', 'B'}, // DF || White-Blue			5
    {'W', 'O'}, // DL || White-Orange		6
    {'W', 'G'}, // DB || White-Green		7
    {'B', 'R'}, // FR || Blue-Red			8
    {'B', 'O'}, // FL || Blue-Orange		9
    {'G', 'R'}, // BR || Green-Red			10
    {'G', 'O'}  // BL || Green-Orange		11
};

// 	White-Orange		6
// 	Blue-Orange			9
//	Green-Red			10
//	Green-Orange		11

const int cornerIndices[CORNER_COUNT][3] = {
    {36, 27, 20},		// YOG || ULB			//T 2
    {38, 18, 11},		// YGR || UBR			//T 1
    {44, 9, 2},			// YRB || URF			//T 2
    {42, 0, 29},		// YBO || UFL			//T 1

    {45, 35, 6},		// WOB || DLF			//T 2
    {47, 8, 15},		// WBR || DFR			//T 1
    {53, 17, 24},		// WRG || DRB			//T 2
    {51, 26, 33},		// WGO || DBL			//T 1
};

	const std::vector<std::string> group0Moves = {
    	"U", "U'", "F", "F'", "R", "R'", "D", "D'", "L", "L'", "B", "B'"
	};
	const std::vector<std::string> group1Moves = {
		"U", "U'", "D", "D'", "R", "R'", "L", "L'", "F2", "B2"
	};
	const std::vector<std::string> group2Moves = {
		"U", "U'", "D", "D'", "R2", "L2", "F2", "B2"
	};
	const std::vector<std::string> group3Moves = {
		"U2", "D2", "R2", "L2", "F2", "B2"
	};

class RubiksCube {
	public:
	


	std::string encodeEdgeOrientationsG0() const;
	static int calculateStateIndexG0(const RubiksCube& cube);
	static bool isEdgeFlippedG0(std::pair<char, char> colors);

	static int encodeCornerOrientationsG1(const RubiksCube& cube);
    static int encodeEdgeSlicePositionsG1(const RubiksCube& cube);
    static int calculateStateIndexG1(const RubiksCube& cube);

	static int calculateStateIndexG2(const RubiksCube& cube);
	static int encodeEdgeSlicePositionsG2(const RubiksCube& cube);
	
	static int calculateStateIndexG3(const RubiksCube& cube);

	int	partialPermIndexer(std::array<uint8_t, 2>& perm) const;
	int	permIndexer(std::array<uint8_t, 4>& perm) const;
	int calculateCornerIndexG3() const;
	int calculateEdgeIndexG3() const;


	bool isEdgeBlueOrGreenG2(int edgeIndex) const;
	int calculateParityG2(const std::vector<int>& permutation) const;
	std::vector<int> getCornerPermutationG2() const;
	int calculateCornerIndexG2() const;

	bool isEdgeInESliceG1(int edgeIndex) const;
	int getCornerOrientationG1(int cornerIndex) const;

	explicit RubiksCube(const std::string& initialState);
	RubiksCube(const RubiksCube& other);

	const std::string& getState() const;

	bool isSolved() const;
	void applyMove(const std::string& moveStr);
    void applyInverseMove(const std::string& moveStr);
    void printCube() const;
    void printState() const;
    void scramble(const std::string& moves);

	std::string state;

	private:

    void moveU();
    void moveUPrime();
    void moveF();
    void moveFPrime();
    void moveR();
    void moveRPrime();
    void moveD();
    void moveDPrime();
    void moveL();
    void moveLPrime();
    void moveB();
    void moveBPrime();
    void moveU2();
    void moveF2();
    void moveR2();
    void moveD2();
    void moveL2();
    void moveB2();

	std::string colorize(const char color) const;
};
