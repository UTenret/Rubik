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

enum EdgePositions {
	UB, UR, UF, UL,
	DR, DF, DL, DB,
	FR, FL, BR, BL,
	EDGE_COUNT
};

enum CornerPositions {
    UBL, UBR, UFR, UFL,
    DBL, DBR, DFR, DFL,
    CORNER_COUNT
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

#define MAX_DEPTH 26
// #define MAX_DEPTH 3
#define G0_N_SOLUTIONS 2048
#define G1_N_SOLUTIONS 1082565

class RubiksCube {
	public:
	
	// namespace ThistleWaite {
        // static std::string encodeEdgeOrientationsG0(const std::string& cube);
        // static int calculateStateIndexG0(const std::string& edgeOrientation);
    // };

	struct Corner {
		char top;
		char left;
		char right;
	};

	static std::string encodeEdgeOrientationsG0(const std::string& cubeState);
	static int calculateStateIndexG0(const std::string& edgeOrientation);
	static bool isEdgeFlippedG0(std::pair<char, char> colors);

	static int encodeCornerOrientationsG1(const RubiksCube& cube);
    static int encodeEdgeSlicePositionsG1(const RubiksCube& cube);
    static int calculateStateIndexG1(const RubiksCube& cube);

	static int calculateStateIndexG2(const RubiksCube& cube);
	static int encodeCornerTetradG2(const RubiksCube& cube);
	static int encodeEdgeSlicePositionsG2(const RubiksCube& cube);
	static int encodeEdgeSlicePositionsG2Debug(const RubiksCube& cube);
	bool isEdgeBlueOrGreenG2(int edgeIndex) const;
	int getCornerTetradPosG2(int cornerIndex) const;
	int calculateParityG2(const std::vector<int>& permutation) const;
	int calculateParityG2Original(const std::vector<int>& permutation) const;
	int calculateParityG2Debug(const std::vector<int>& permutation) const;
	std::vector<int> getCornerPermutationG2() const;
	std::vector<int> getEdgePermutationG2() const;
	int rank() const;
	int rankEdge(const std::array<int, 4> comb) const;

	int getCornerOrientationG1(int cornerIndex) const;
	bool isEdgeInESliceG1(int edgeIndex) const;

	explicit RubiksCube(const std::string& initialState);
	RubiksCube(const RubiksCube& other);

	const std::string& getState() const;

	bool isSolved() const;
	void applyMove(const std::string& moveStr);
    void applyInverseMove(const std::string& moveStr);
    void printCube() const;
    void printState() const;
    void scramble(const std::string& moves);

	void calculateCornerTetradIndex() const;
	static void IsCornerInCorrectTetrad(const RubiksCube& cube);

	void CalculateCycles();


	private:

	std::string state;

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

extern std::set<int> UniqueEdgeIndex;
extern std::map<int, std::set<int>> cornerToEdgeIndexMap;
extern std::map<int, std::set<int>> edgeToCornerIndexMap;
extern std::map<std::pair<int, int>, std::set<int>> cornerEdgeToParityMap;