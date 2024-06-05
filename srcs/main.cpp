#include "RubiksCube.hpp"
#include "ThistlewaiteSolver.hpp"
#include "visualizer.hpp"
#include <regex>
#include <algorithm>

std::vector<std::string> splitString(const std::string& str, char delimiter = ' ') {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

bool isValidMove(const std::string& move) {
    static const std::regex moveRegex("^(U|D|L|R|F|B|U'|D'|L'|R'|F'|B'|U2|D2|L2|F2|B2|R2)$");
    return std::regex_match(move, moveRegex);
}

bool isValidScramble(const std::string& scramble) {
    std::vector<std::string> moves = splitString(scramble);
    for (const auto& move : moves) {
        if (!isValidMove(move)) {
            return false;
        }
    }
    return true;
}

void printUsage() {
    std::cout << "Usage: ./RubiksCubeSolver <scramble> [--novisualizer]\n";
    std::cout << "  <scramble> : A valid scramble sequence (e.g., \"U F2 R' D B2 L2\")\n";
    std::cout << "  [--novisualizer] : Optional flag to run without the visualizer\n";
}

std::string rescramble(std::string result) {
    std::string initialState = 
    "BBBBBBBBB"
    "RRRRRRRRR"
    "GGGGGGGGG"
    "OOOOOOOOO"
    "YYYYYYYYY"
    "WWWWWWWWW";

    RubiksCube cube(initialState);
    PruningTable table(cube);
    std::string scramble = result;
    cube.scramble(scramble);
    ThistlewaiteSolver solver(cube, table);
    solver.solveCube();
    std::string solution = solver.fullSolution;
    return solution;
}

int main(int argc, char* argv[]) {
    std::string initialState = 
    "BBBBBBBBB"  // FRONT: 0 - 8
    "RRRRRRRRR"  // RIGHT: 9 - 17
    "GGGGGGGGG"  // BACK: 18 - 26
    "OOOOOOOOO"  // LEFT: 27 - 35
    "YYYYYYYYY"  // UP: 36 - 44
    "WWWWWWWWW"; // DOWN: 45 - 53

    bool useVisualizer = true;

    if (argc < 2 || argc > 3) {
        std::cout << "Error: Invalid number of parameters.\n";
        printUsage();
        return 1;
    }

    std::string scramble = argv[1];
    if (argc == 3) {
        std::string option = argv[2];
        std::transform(option.begin(), option.end(), option.begin(), ::tolower);
        if (option == "--novisualizer") {
            useVisualizer = false;
        } else {
            std::cout << "Error: Invalid option.\n";
            printUsage();
            return 1;
        }
    }

    if (!isValidScramble(scramble)) {
        std::cout << "Error: Invalid scramble sequence.\n";
        printUsage();
        return 1;
    }

    RubiksCube cube(initialState);
    PruningTable table(cube);

    table.generateMissingLUTs();

    cube.scramble(scramble);

    ThistlewaiteSolver solver(cube, table);
    solver.solveCube();

    std::string solution = solver.fullSolution;

    std::vector<std::string> moves = splitString(solution);
    for (const auto& move : moves) {
        cube.applyMove(move);
    }

    if (useVisualizer) {
        visualizer(argc, argv, solution);
    } else {
    	cube.printCube();
    }

    return 0;
}
