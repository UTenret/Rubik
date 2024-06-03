#pragma once

#include <functional>
#include "RubiksCube.hpp"
#include "PruningTable.hpp"

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
