#pragma once

#include <functional>
#include "RubiksCube.hpp"
#include "PruningTable.hpp"

class Solver {
public:
	typedef std::string (*EncodeStateFunc)(const std::string&);
	typedef int (*CalculateIndexFunc)(const std::string&);

	explicit Solver(const RubiksCube& cube, const PruningTable& table) : cube(cube), table(table) {}

	bool iddfs(int depth, int maxDepth, std::vector<std::string>& solution, 
           std::function<bool ()> isSolved,
           const std::vector<std::string>& allowedMoves);

	void solveCube();
	
	void iterativeSolve(
		const std::vector<int>& lut,
		const std::vector<std::string>& moves,
		EncodeStateFunc encodeState,
		CalculateIndexFunc calculateIndex,
		std::vector<std::string>& solution
	);
	void solveGroup(std::function<bool()> groupSolveCondition, const std::vector<std::string>& moves);

	bool isMovePrunable(const std::string& lastMove, const std::string& currentMove);

private:

	RubiksCube cube;
	PruningTable table;
};
