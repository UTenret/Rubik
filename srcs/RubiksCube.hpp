#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <set>
#include <cmath>
#include <queue>
#include <cstring>

class RubiksCube {
	public:
	
	explicit RubiksCube(const std::string& initialState);

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