#include "ThistlewaiteSolver.hpp"
#include "Group0.hpp"
#include "Group1.hpp"
#include "Group2.hpp"
#include "Group3.hpp"

// can improve by directly identifying which group this belongs to and not loading unecessary
// luts or useless functions calls, same thing if group0 solves the cube for example
// + symmetry

void printExplanation(int phase)
{
	switch (phase){
		case 0:
            std::cout << MAGENTA << "===== Phase 1: Edge Orientation =====" << RESET << std::endl;
			std::cout << WHITE << "During this phase, all 12 edges should be oriented correctly, considering two orientations for each. The orientations of 11 determine the 12th (because every twist either flips 0 or 4 edges, the total edge orientation is always divisible by 2, so only 1/2 of the edge permutation orientations are reachable)." << std::endl;
            std::cout << WHITE << "Therefore, there are" << CYAN << " 2¹¹ = 2048 " << WHITE << "states total." << std::endl;
			std::cout << CYAN << "Target subgroup: {F, B, L, R, U, D}" << std::endl;
			break ;
		case 1:
            std::cout << MAGENTA << "===== Phase 2: Top and Bottom Colors =====" << RESET << std::endl;
			std::cout << WHITE << "During this phase, all M-slice edges should be placed correctly, and corner orientations should be solved. For the M-edges, there are 12C4 combinations: 4 edges and 12 positions, regardless of order. For the corners, the orientations of 7 determine the 8th (because the total orientation of the corners is always divisible by 3, so only 1/3 of the corner orientation permutations are reachable)." << std::endl;
            std::cout << WHITE << "Therefore, there are" << CYAN << " 12C4 * 3⁷ = 1082565" << WHITE << " states total." << std::endl;
			std::cout << CYAN << "Target subgroup: {F2, B2, L, R, U, D}" << std::endl;
			break ;
		case 2:
            std::cout << MAGENTA << "===== Phase 3: All Colors Combination =====" << RESET << std::endl;
			std::cout << WHITE << "During this phase, all edges and all corners should be in their slices/orbits. Tetrad-paired corners create unique pairs, totaling 4 combinations due to 8 corners. This results in 8C2*6C2*4C2 = 2520 elements. For the edges, there are 8C4 combinations due to 8 positions and 4 edges (M-slice already solved). Parity is accounted for, doubling the elements." << std::endl;
            std::cout << WHITE << "Therefore, there are" << CYAN << " 8C2 * 6C2 * 4C2 * 8C4 * 2 = 352800" << WHITE << " states total." << std::endl;
			std::cout << CYAN << "Target subgroup: {F2, B2, L2, R2, U, D}" << std::endl;
			break ;
		default:
            std::cout << MAGENTA << "===== Phase 4: Final Solution with Half-Turns =====" << RESET << std::endl;
			std::cout << WHITE << "For the edges, each slice's 4 edges can be permuted in 4! ways, giving 4!^3 permutations. However, edge parity is fixed, allowing only half of these states. With 10 edges solved, the remaining 2 must also be solved as it's not possible to make just one swap. Similarly, corners have even parity since previous phase, halving the reachable permutations of 4!^2. Additionally, fixed tetrad twists mean 3-cycle twists of corners aren't possible. Thus, only 4!4!/(2*3) = 96 corner permutations are reachable." << std::endl;
            std::cout << WHITE << "Therefore, there are" << CYAN << " 4!³ / 2 * 96 = 663552" << WHITE << " states total." << std::endl;
			std::cout << CYAN << "Target subgroup: {F2, B2, L2, R2, U2, D2}" << std::endl;
			break ;
	}
}

void ThistlewaiteSolver::solveCube() {
    std::vector<std::vector<std::string>> solution(4);

    table.setLUT(0, table.loadLUTFromFile("Database/Thistlewaite/G0.txt", G0_N_SOLUTIONS));
    table.setLUT(1, table.loadLUTFromFile("Database/Thistlewaite/G1.txt", G1_N_SOLUTIONS));
    table.setLUT(2, table.loadLUTFromFile("Database/Thistlewaite/G2.txt", G2_N_SOLUTIONS));
    table.setLUT(3, table.loadLUTFromFile("Database/Thistlewaite/G3.txt", G3_N_SOLUTIONS));

    iterativeSolve(table.getLUT(0), Group0::moves, Group0::calculateStateIndex, solution[0]);
    iterativeSolve(table.getLUT(1), Group1::moves, Group1::calculateStateIndex, solution[1]);
    iterativeSolve(table.getLUT(2), Group2::moves, Group2::calculateStateIndex, solution[2]);
    iterativeSolve(table.getLUT(3), Group3::moves, Group3::calculateStateIndex, solution[3]);

    for (unsigned long i = 0; i < solution.size(); i++) {
        printExplanation(i);
        std::string group = "G" + std::to_string(i) + "-G" + std::to_string(i + 1);
        if (!solution[i].empty()) {
            std::cout << GREEN << "Phase moves: ";
            for (const auto& move : solution[i]) std::cout << move << " ";
            std::cout << std::endl << std::endl;
        } else {
            std::cout << GREEN << "Cube already solved for this phase" << std::endl;
        }
    }

    std::vector<std::string> combinedSolution;
    std::cout << "===== Full solution =====" << WHITE << std::endl;
    for (const auto& groupSolution : solution) {
        combinedSolution.insert(combinedSolution.end(), groupSolution.begin(), groupSolution.end());
    }

    std::vector<std::string> simplifiedSolution = simplifySolution(combinedSolution);
    fullSolution.clear();
    for (const auto& move : simplifiedSolution) {
        fullSolution += move + " ";
    }
    std::cout << fullSolution << GREEN << std::endl;
    std::cout << "Total moves: " << WHITE << simplifiedSolution.size() << RESET << std::endl;
}

void ThistlewaiteSolver::iterativeSolve(
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

std::vector<std::string> ThistlewaiteSolver::simplifySolution(const std::vector<std::string>& solution) {
    std::vector<std::string> simplified;

    for (const auto& move : solution) {
        if (!simplified.empty()) {
            std::string lastMove = simplified.back();

            if (lastMove.front() == move.front()) {
                char face = lastMove.front();
                int lastCount = (lastMove.length() == 1) ? 1 : (lastMove[1] == '2' ? 2 : -1);
                int currentCount = (move.length() == 1) ? 1 : (move[1] == '2' ? 2 : -1);
                int newCount = lastCount + currentCount;

                if (newCount % 4 == 0) {
                    simplified.pop_back();
                    continue;
                }

                if (newCount % 4 == 2) {
                    simplified.back() = face + std::string("2");
                    continue;
                }

                if (newCount % 4 == 1) {
                    simplified.back() = face + std::string("");
                    continue;
                }

                if (newCount % 4 == 3) {
                    simplified.back() = face + std::string("'");
                    continue;
                }
            }
        }

        simplified.push_back(move);
    }

    return simplified;
}
