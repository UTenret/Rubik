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
    {'Y', 'G'}, // UB || Yellow-Green
    {'Y', 'R'}, // UR || Yellow-Red
    {'Y', 'B'}, // UF || Yellow-Blue
    {'Y', 'O'}, // UL || Yellow-Orange
    {'W', 'R'}, // DR || White-Red
    {'W', 'B'}, // DF || White-Blue
    {'W', 'O'}, // DL || White-Orange
    {'W', 'G'}, // DB || White-Green
    {'B', 'R'}, // FR || Blue-Red
    {'B', 'O'}, // FL || Blue-Orange
    {'G', 'R'}, // BR || Green-Red
    {'G', 'O'}  // BL || Green-Orange
};

const int cornerIndices[CORNER_COUNT][3] = {
    {36, 27, 18},
    {38, 9, 20},
    {44, 11, 2},
    {42, 0, 29},
    {53, 33, 24},
    {51, 15, 26},
    {47, 17, 8},
    {45, 35, 6}
};

#define MAX_DEPTH 9
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

	int getCornerOrientationG1(int cornerIndex) const;
	bool isEdgeInESliceG1(int edgeIndex) const;

	explicit RubiksCube(const std::string& initialState);
	RubiksCube(const RubiksCube& other);

	const std::string& getState() const;

	bool isSolved() const;
	void applyMove(const std::string& moveStr);
    void applyInverseMove(const std::string& moveStr);
    void printCube() const;
    void scramble(const std::string& moves);

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