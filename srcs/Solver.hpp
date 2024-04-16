#pragma once

#include "RubiksCube.hpp"
#include "PruningTable.hpp"

class Solver {
public:
	typedef std::string (*EncodeStateFunc)(const std::string&);
	typedef int (*CalculateIndexFunc)(const std::string&);

	explicit Solver(const RubiksCube& cube, const PruningTable& table) : cube(cube), table(table) {}

	bool iddfs(int depth, int maxDepth, std::vector<std::string>& solution, 
			bool (*isSolved)(const std::string&), const std::vector<std::pair<void(*)(std::string&),
			std::string>>& allowedMoves);

	void solveCube(const std::vector<int>& lut);
	
	void iterativeSolve(
		const std::vector<int>& lut,
		const std::vector<std::string>& moves,
		EncodeStateFunc encodeState,
		CalculateIndexFunc calculateIndex,
		std::vector<std::string>& solution
	);

	bool isMovePrunable(const std::string& lastMove, const std::string& currentMove);
	int calculateStateIndexG0(const std::string& edgeOrientation);
	std::string encodeEdgeOrientationsG0(const std::string& cube);
	bool isEdgeFlipped(std::pair<char, char> colors);

private:

	RubiksCube cube;
	PruningTable table;
};
