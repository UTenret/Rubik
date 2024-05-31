#pragma once

#include <functional>
#include "RubiksCube.hpp"
#include "PruningTable.hpp"

class ThistlewaiteSolver {
public:
	typedef int (*CalculateIndexFunc)(const RubiksCube&);

	explicit ThistlewaiteSolver(const RubiksCube& cube, const PruningTable& table) : cube(cube), table(table) {}

	void solveCube();
	
	void iterativeSolve(
		const std::vector<int>& lut,
		const std::vector<std::string>& moves,
		CalculateIndexFunc calculateIndex,
		std::vector<std::string>& solution
	);

	bool isMovePrunable(const std::string& lastMove, const std::string& currentMove);

private:

	RubiksCube cube;
	PruningTable table;
};
