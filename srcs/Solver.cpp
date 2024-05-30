#include "Solver.hpp"

bool Solver::iddfs(int depth, int maxDepth, std::vector<std::string>& solution, 
			std::function<bool()> isSolved,
			 const std::vector<std::string>& allowedMoves) {
	if(isSolved()){
		cube.printCube();
		std::cout << "FULL SOLUTION :";
		for (const auto& move : solution) {
			std::cout << move << " ";
		}
		std::cout << std::endl;
		return true;
	}

	if(depth == maxDepth) {
		// std::cout << "Max depth reached without a solution" << std::endl;
		return false;
	}

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

// can improve by directly identifying which group this belongs to and not loading unecessary
// luts or useless functions calls, same thing if group0 solves the cube for example
// + symmetry

void Solver::solveCube() {
	std::vector<std::vector<std::string>> solution(4);

	const std::vector<std::string> group0Moves = {
    	"U", "U'", "F", "F'", "R", "R'", "D", "D'", "L", "L'", "B", "B'"
	};
    const std::vector<std::string> group1Moves = {
		"U", "U'", "D", "D'", "R", "R'", "L", "L'", "F2", "B2"
	};
	const std::vector<std::string> group2Moves = { // no F, F', B, B', L, L', R, R'
		"U", "U'", "D", "D'", "L2", "R2", "F2", "B2"
    };
	const std::vector<std::string> group3Moves = { // only half turn moves
		"U2", "D2", "L2", "R2", "F2", "B2"
    };

	table.setLUT(0, table.loadLUT("G0.txt", G0_N_SOLUTIONS));
	table.setLUT(1, table.loadLUT("G1.txt", G1_N_SOLUTIONS));
	table.setLUT(2, table.loadLUT("G2.txt", G2_N_SOLUTIONS));
	table.setLUT(3, table.loadLUT("G3.txt", G3_N_SOLUTIONS));

	iterativeSolve(table.getLUT(0),
					group0Moves,
					  RubiksCube::calculateStateIndexG0,
					   solution[0]);
	
	iterativeSolve(table.getLUT(1),
					group1Moves,
					  RubiksCube::calculateStateIndexG1,
					   solution[1]);

	iterativeSolve(table.getLUT(2),
					group2Moves,
					  RubiksCube::calculateStateIndexG2,
					   solution[2]);

	iterativeSolve(table.getLUT(3),
					group3Moves,
					  RubiksCube::calculateStateIndexG3,
					   solution[3]);
	for (int i = 0; i < solution.size(); i++) {
		std::string group = "G" + std::to_string(i) + "-G" + std::to_string(i+1);
		if (!solution[i].empty()) {
			std::cout << "Solution found for " << group << " transition: ";
			for (const auto& move : solution[i]) std::cout << move << " ";
			std::cout << std::endl;
			// std::cout << std::endl << "After " << group << std::endl;
			// cube.printCube(); if I print here it will always be solved as cube has been solved
			// still need group visu but need to think about it
		}
		else std::cout << "Cube already solved for " << group << std::endl;
	}
	int totalMoves = 0;
	std::cout << "Cube has been solved, full solution :";
	for (const auto& groupSolution : solution) {
		totalMoves += groupSolution.size();
		for (const auto& move : groupSolution) std::cout << move << " ";
	}
	std::cout << std::endl << "Number of moves: " << totalMoves << std::endl;
	// WE NEED TO PRUNE MOVES !!! R L L2 R2 is prunable into R' L'
	cube.printCube();
    // solveGroup([this]() { return cube.isSolved(); }, group3Moves, solution);
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

void Solver::solveGroup(std::function<bool()> groupSolveCondition, const std::vector<std::string>& moves, std::vector<std::string> solution) {
    for (int i = 1; i < MAX_DEPTH; i++) {
        if (iddfs(0, i, solution, groupSolveCondition, moves))
            break;
    }
}

void Solver::iterativeSolve(
    const std::vector<int>& lut,
    const std::vector<std::string>& moves,
    CalculateIndexFunc calculateIndex,
    std::vector<std::string>& solution
) {
    bool progress = true;

    while (progress) {
        progress = false;
        int currentStateIndex = calculateIndex(cube);
        int currentDistance = lut[currentStateIndex];

        if (currentDistance == 0) break;

        for (const auto& move : moves) {
            cube.applyMove(move);
            int newStateIndex = calculateIndex(cube);
            if (lut[newStateIndex] < currentDistance) {

                solution.push_back(move);

                progress = true;
                break;
            } else {
                cube.applyInverseMove(move);
            }
        }
    }
}
