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

	bool isSolved(const std::string& cube) const;
	void applyMove(std::string& cube, const std::string& moveStr);
    void applyInverseMove(std::string& cube, const std::string& moveStr);
    void printCube(const std::string& cube) const;

	private:

	std::string state;

    void moveU(std::string& cube);
    void moveUPrime(std::string& cube);
    void moveF(std::string& cube);
    void moveFPrime(std::string& cube);
    void moveR(std::string& cube);
    void moveRPrime(std::string& cube);
    void moveD(std::string& cube);
    void moveDPrime(std::string& cube);
    void moveL(std::string& cube);
    void moveLPrime(std::string& cube);
    void moveB(std::string& cube);
    void moveBPrime(std::string& cube);
    void moveU2(std::string& cube);
    void moveF2(std::string& cube);
    void moveR2(std::string& cube);
    void moveD2(std::string& cube);
    void moveL2(std::string& cube);
    void moveB2(std::string& cube);

	std::string colorize(char piece) const;

};