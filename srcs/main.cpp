#include "RubiksCube.hpp"
#include "ThistlewaiteSolver.hpp"
#include "visualizer.hpp"
#include <regex>

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
	std::cout << "move: " << move << std::endl;
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
    std::cout << "Usage: ./RubiksCubeSolver <scramble>\n";
    std::cout << "  <scramble> : A valid scramble sequence (e.g., \"U F2 R' D B2 L2\")\n";
}

std::string    rescramble(std::string result) {
	std::string initialState = 
    "BBBBBBBBB"
    "RRRRRRRRR"
    "GGGGGGGGG"
    "OOOOOOOOO"
    "YYYYYYYYY"
    "WWWWWWWWW";

	RubiksCube	cube(initialState);
	PruningTable	table(cube);
    std::string scramble = result;
    cube.scramble(scramble);
    ThistlewaiteSolver	ThistlewaiteSolver(cube, table);
	ThistlewaiteSolver.solveCube();
	std::string solution = ThistlewaiteSolver.fullSolution;
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

    if (argc != 2) {
        std::cout << "Error: Invalid number of parameters.\n";
        printUsage();
        return 1;
    }

    std::string scramble = argv[1];
    if (!isValidScramble(scramble)) {
        std::cout << "Error: Invalid scramble sequence.\n";
        printUsage();
        return 1;
    }

    RubiksCube cube(initialState);
    PruningTable table(cube);

    table.generateMissingLUTs();

    cube.scramble(scramble);
    // cube.printCube();

    ThistlewaiteSolver solver(cube, table);
    solver.solveCube();

    std::string solution = solver.fullSolution;
    visualizer(argc, argv, solution);

    return 0;
}
