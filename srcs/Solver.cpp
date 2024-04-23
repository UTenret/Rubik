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

void Solver::solveCube() {
	std::vector<std::string> solution;

	// std::vector<std::string> group0Moves = {
    // 	"U", "U'", "F", "F'", "R", "R'", "D", "D'", "L", "L'", "B", "B'", 
    // 	"U2", "F2", "R2", "D2", "L2", "B2"
	// };

	const std::vector<std::string> group0Moves = {
    	"U", "U'", "F", "F'", "R", "R'", "D", "D'", "L", "L'", "B", "B'",
	};

    // Pass lambdas to the function
	table.setLUT(0, table.loadLUT("G0.txt", 2048));
	iterativeSolve(table.getLUT(0),
					group0Moves,
					 RubiksCube::encodeEdgeOrientationsG0,
					  RubiksCube::calculateStateIndexG0,
					   solution);
    std::cout << "AFTER G0->G1" << std::endl;
	cube.printCube();

    std::vector<std::string> group1Moves = { // no F, F', B, B'
		{"U"},
		{"U'"},
		{"R"},
		{"R'"},
		{"D"},
		{"D'"},
		{"L"},
		{"L'"},
		{"F2"},
		{"B2"},
    };

	solution.clear();
	table.setLUT(1, table.loadLUT("G1.txt", 1082565));
	iterativeSolveG1(table.getLUT(1), group1Moves, solution);


	std::vector<std::string> group2Moves = { // no F, F', B, B', L, L', R, R'
		{"U"},
		{"U'"},
		{"D"},
		{"D'"},
		{"L2"},
		{"R2"},
		{"F2"},
		{"B2"},
    };
    std::cout << "AFTER G1->G2" << std::endl;
	cube.printCube();

    solveGroup([this]() { return cube.isSolved(); }, group2Moves, solution);
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
    EncodeStateFunc encodeState,
    CalculateIndexFunc calculateIndex,
    std::vector<std::string>& solution
) {
    bool progress = true;

    while (progress) {
        progress = false;
        std::string currentStateEncoded = encodeState(cube.getState());
		// std::cout << "cube.getState(): " << cube.getState() << std::endl;
		// std::cout << "currentStateEncoded: " << currentStateEncoded << std::endl;
		// std::cout << "cube.getState(): " << cube.getState() << std::endl;
        int currentDistance = lut[calculateIndex(currentStateEncoded)];
		// std::cout << "calculateIndex(currentStateEncoded) : " << calculateIndex(currentStateEncoded) << std::endl;
		// std::cout << "calculateIndex(currentStateEncoded) : " << calculateIndex(currentStateEncoded) << std::endl;
		// std::cout << "currentDistance: " << currentDistance << std::endl;
		// cube.printCube();

        if (currentDistance == 0) {
			if (solution.empty()) {
				std::cout << "Cube is already solved for G0-G1 transition." << std::endl;
				break;
			}
            std::cout << "Solution found for G0-G1 transition.: ";
            for (const auto& move : solution) std::cout << move << " ";
            std::cout << "\n";
            break;
        }
        for (const auto& move : moves) {
            cube.applyMove(move);
            std::string newStateEncoded = encodeState(cube.getState());
            int newIndex = calculateIndex(newStateEncoded);
            if (lut[newIndex] < currentDistance) {
                solution.push_back(move);
				std::cout << "newIndex: " << newIndex << std::endl;
                progress = true;
                break;
            } else {
                cube.applyInverseMove(move);
            }
        }
    }

    if (!progress && solution.empty() && lut[calculateIndex(encodeState(cube.getState()))] != 0) {
        std::cout << "No solution found with the given LUT and moves.\n";
    }
}

void Solver::iterativeSolveG1(
    const std::vector<int>& lut,
    const std::vector<std::string>& moves,
    std::vector<std::string>& solution
) {
    bool progress = true;

    while (progress) {
        progress = false;
        int currentStateIndex = RubiksCube::calculateStateIndexG1(cube);
        int currentDistance = lut[currentStateIndex];

        if (currentDistance == 0) {
            if (solution.empty()) {
                std::cout << "Cube is already solved for G1-G2 transition." << std::endl;
                break;
            }
			std::cout << "currentStateIndex: " << currentStateIndex << std::endl;
            std::cout << "Solution found for G1-G2 transition: ";
            for (const auto& move : solution) std::cout << move << " ";
            std::cout << "\n";
            break;
        }

        for (const auto& move : moves) {
            cube.applyMove(move);
            int newStateIndex = RubiksCube::calculateStateIndexG1(cube);
            if (lut[newStateIndex] < currentDistance) {
                solution.push_back(move);
                progress = true;
                break;  // Stop after finding the first productive move
            } else {
                cube.applyInverseMove(move);  // Undo the move if it doesn't reduce distance
            }
        }
    }

    if (!progress && solution.empty() && lut[RubiksCube::calculateStateIndexG1(cube)] != 0) {
        std::cout << "No solution found with the given LUT and moves for G1-G2." << std::endl;
    }
}
