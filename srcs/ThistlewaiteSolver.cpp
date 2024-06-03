#include "ThistlewaiteSolver.hpp"
#include "Group0.hpp"
#include "Group1.hpp"
#include "Group2.hpp"
#include "Group3.hpp"

// can improve by directly identifying which group this belongs to and not loading unecessary
// luts or useless functions calls, same thing if group0 solves the cube for example
// + symmetry
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

    for (int i = 0; i < solution.size(); i++) {
        std::string group = "G" + std::to_string(i) + "-G" + std::to_string(i + 1);
        if (!solution[i].empty()) {
            std::cout << "Solution found for " << group << " transition: ";
            for (const auto& move : solution[i]) std::cout << move << " ";
            std::cout << std::endl;
        } else {
            std::cout << "Cube already solved for " << group << std::endl;
        }
    }

    std::vector<std::string> combinedSolution;
    for (const auto& groupSolution : solution) {
        combinedSolution.insert(combinedSolution.end(), groupSolution.begin(), groupSolution.end());
    }
    std::cout << "Number of moves before pruning: " << combinedSolution.size() << std::endl;

    std::vector<std::string> simplifiedSolution = simplifySolution(combinedSolution);
    fullSolution.clear();
    for (const auto& move : simplifiedSolution) {
        fullSolution += move + " ";
    }

    std::cout << "Cube has been solved, full solution: " << fullSolution << std::endl;
    std::cout << "Number of moves: " << simplifiedSolution.size() << std::endl;

    cube.printCube();
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
