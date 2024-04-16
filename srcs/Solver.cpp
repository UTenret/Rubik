#include "Solver.hpp"

bool Solver::iddfs(int depth, int maxDepth, std::vector<std::string>& solution, 
			std::function<bool()> isSolved,
			 const std::vector<std::string>& allowedMoves) {
	if(isSolved()){
		cube.printCube();
		std::cout << "SOLUTION :";
		for (const auto& move : solution) {
			std::cout << move << " ";
		}
		std::cout << std::endl;
		return true;
	}

	if(depth == maxDepth)
		return false;

	for (const auto& moveStr : allowedMoves) {
		if (!solution.empty() && isMovePrunable(solution.back(), moveStr)) {
            continue;
        }
		// moveFunc();
		cube.applyMove(moveStr);
		solution.push_back(moveStr);
		if (iddfs(depth + 1, maxDepth, solution, isSolved, allowedMoves)) {
			return true;
		}
		cube.applyInverseMove(moveStr); 
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

    // Pass lambdas to the function
	iterativeSolve(lut,
					group0Moves,
					 RubiksCube::encodeEdgeOrientationsG0,
					  RubiksCube::calculateStateIndexG0,
					   solution);
    
    std::vector<std::string> group1Moves = { // no F, F', B, B'
		{"U"},
		{"U'"},
		{"R"},
		{"R'"},
		{"D"},
		{"D'"},
		{"L"},
		{"L'"},
		{"U2"},
		{"F2"},
		{"R2"},
		{"D2"},
		{"L2"},
		{"B2"},
    };
    
    solveGroup([this]() { return cube.isSolved(); }, group1Moves);
}

bool Solver::isMovePrunable(const std::string& lastMove, const std::string& currentMove) {
    if (lastMove.front() == currentMove.front()) {
        if ((lastMove == "U" && currentMove == "U'") || (lastMove == "U'" && currentMove == "U") ||
            (lastMove == "R" && currentMove == "R'") || (lastMove == "R'" && currentMove == "R") ||
            (lastMove == "F" && currentMove == "F'") || (lastMove == "F'" && currentMove == "F") ||
            (lastMove == "D" && currentMove == "D'") || (lastMove == "D'" && currentMove == "D") ||
            (lastMove == "L" && currentMove == "L'") || (lastMove == "L'" && currentMove == "L") ||
            (lastMove == "B" && currentMove == "B'") || (lastMove == "B'" && currentMove == "B")) {
            return true;
        }
        else if (lastMove == currentMove) {
            return true;
        }
    }
    return false;
}

void Solver::solveGroup(std::function<bool()> groupSolveCondition, const std::vector<std::string>& moves) {
    std::vector<std::string> solution;
    for (int i = 1; i < MAX_DEPTH; i++) {
        if (iddfs(0, i, solution, groupSolveCondition, moves))
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
        std::string currentStateEncoded = encodeState(cube.getState());
        int currentDistance = lut[calculateIndex(currentStateEncoded)];

        if (currentDistance == 0) {
            std::cout << "Solution found: ";
            for (const auto& move : solution) std::cout << move << " ";
            std::cout << "\n";
            break;
        }

        for (const auto& move : moves) {
            RubiksCube currentCube(cube);
            cube.applyMove(newState, move);
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
