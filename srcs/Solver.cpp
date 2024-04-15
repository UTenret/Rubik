#include "Solver.hpp"

bool Solver::iddfs(int depth, int maxDepth, std::vector<std::string>& solution, 
			bool (*isSolved)(std::string&), const std::vector<std::pair<void(*)(std::string&), std::string>>& allowedMoves) {
	// if(isSolved(cube) || isFullySolved(cube)) {
	if(isSolved(cube)){
		cube.printCube(cube);
		std::cout << "SOLUTION :";
		for (const auto& move : solution) {
			std::cout << move << " ";
		}
		std::cout << endl;
		return true;
	}
	if(depth == maxDepth)
		return false;

	for (auto& [moveFunc, moveStr] : allowedMoves) {
		if (!solution.empty() && isMovePrunable(solution.back(), moveStr)) {
            continue;
        }
		moveFunc(cube);
		solution.push_back(moveStr);
		if (iddfs(cube, depth + 1, maxDepth, solution, isSolved, allowedMoves)) {
			return true;
		}
		applyInverseMove(cube, moveStr); 
		solution.pop_back();
	}
	return false;
}

void Solver::solveCube(const std::vector<int>& lut) {
	std::vector<std::string> solution;

	std::vector<std::string> group0Moves = {
    	"U", "U'", "F", "F'", "R", "R'", "D", "D'", "L", "L'", "B", "B'", 
    	"U2", "F2", "R2", "D2", "L2", "B2"
	};

	iterativeSolve(lut, group0Moves, encodeEdgeOrientationsG0, calculateStateIndexG0, solution);
    
    std::vector<std::pair<void(*)(std::string&), std::string>> group1Moves = { // no F, F', B, B'
		{cubemoveU, "U"},
		{moveUPrime, "U'"},
		{moveR, "R"},
		{moveRPrime, "R'"},
		{moveD, "D"},
		{moveDPrime, "D'"},
		{moveL, "L"},
		{moveLPrime, "L'"},
		{moveU2, "U2"},
		{moveF2, "F2"},
		{moveR2, "R2"},
		{moveD2, "D2"},
		{moveL2, "L2"},
		{moveB2, "B2"},
    };
    
    solveGroup(cube, isFullySolved, group1Moves);
}

void solveGroup(std::string& cube, bool (*groupSolveCondition)(std::string&), const std::vector<std::pair<void(*)(std::string&), std::string>>& moves) {
    std::vector<std::string> solution;
    for (int i = 1; i < MAX_DEPTH; i++) {
        if (iddfs(cube, 0, i, solution, groupSolveCondition, moves))
            break;
    }
}

void Solver::iterativeSolve(
    const std::vector<int>& lut,
    const std::vector<std::string>& moves,
    EncodeStateFunc encodeState,
    CalculateIndexFunc calculateIndex,
    std::vector<std::string>& solution
) {
    bool progress = true;

    while (progress) {
        progress = false;
        std::string currentStateEncoded = encodeState(cube);
        int currentDistance = lut[calculateIndex(currentStateEncoded)];

        if (currentDistance == 0) {
            std::cout << "Solution found: ";
            for (const auto& move : solution) std::cout << move << " ";
            std::cout << "\n";
            break;
        }

        for (const auto& move : moves) {
            std::string newState = cube;
            applyMove(newState, move);
            std::string newStateEncoded = encodeState(newState);
            int newIndex = calculateIndex(newStateEncoded);
            if (lut[newIndex] < currentDistance) {
                cube = newState;
                solution.push_back(move);
                progress = true;
                break;
            }
        }
    }

    if (!progress && solution.empty()) {
        std::cout << "No solution found with the given LUT and moves.\n";
    }
}