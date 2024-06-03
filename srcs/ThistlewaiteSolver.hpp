#pragma once

#include <functional>
#include "RubiksCube.hpp"
#include "PruningTable.hpp"

const std::string RESET = "\033[0m";
const std::string RED = "\033[1;31m";
const std::string GREEN = "\033[1;32m";
const std::string BLUE = "\033[1;34m";
const std::string MAGENTA = "\033[1;35m";
const std::string CYAN = "\033[1;36m";
const std::string WHITE = "\033[1;37m";

class ThistlewaiteSolver {
public:
	std::string fullSolution;
	typedef int (*CalculateIndexFunc)(const RubiksCube&);

	explicit ThistlewaiteSolver(const RubiksCube& cube, const PruningTable& table) : cube(cube), table(table) {}

	void solveCube();
	
	void iterativeSolve(
		const std::vector<int>& lut,
		const std::vector<std::string>& moves,
		CalculateIndexFunc calculateIndex,
		std::vector<std::string>& solution
	);

	std::vector<std::string> simplifySolution(const std::vector<std::string>& solution);


private:

	RubiksCube cube;
	PruningTable table;
};

std::string    rescramble(std::string result);
