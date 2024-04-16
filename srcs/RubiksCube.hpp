#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <set>
#include <cmath>
#include <queue>
#include <cstring>

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
#define G0_N_SOLUTIONS 2048
#define G1_N_SOLUTIONS 1082565

class RubiksCube {
	public:
	
	// namespace ThistleWaite {
        // static std::string encodeEdgeOrientationsG0(const std::string& cube);
        // static int calculateStateIndexG0(const std::string& edgeOrientation);
    // };

	static std::string encodeEdgeOrientationsG0(const std::string& cubeState);
	static int calculateStateIndexG0(const std::string& edgeOrientation);
	static bool isEdgeFlipped(std::pair<char, char> colors);


	explicit RubiksCube(const std::string& initialState);
	RubiksCube(const RubiksCube& other);

	const std::string& getState() const;
	const std::string& getState() const;

	bool isSolved() const;
	void applyMove(const std::string& moveStr);
    void applyInverseMove(const std::string& moveStr);
    void printCube() const;

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