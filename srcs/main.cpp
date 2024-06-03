#include "RubiksCube.hpp"
#include "ThistlewaiteSolver.hpp"
#include "visualizer.hpp"

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

int main(int argc, char* argv[]) {
	std::string initialState = 
    "BBBBBBBBB"  // FRONT: 0 - 8
    "RRRRRRRRR"  // RIGHT: 9 - 17
    "GGGGGGGGG"  // BACK: 18 - 26
    "OOOOOOOOO"  // LEFT: 27 - 35
    "YYYYYYYYY"  // UP: 36 - 44
    "WWWWWWWWW"; // DOWN: 45 - 53

	RubiksCube		cube(initialState);
	PruningTable	table(cube);
	if (argc > 2)
		table.generateLUT();
	if (argc > 1) {
		std::string scramble = argv[1];
		cube.scramble(argv[1]);
		cube.printCube();
	}
	else {
		std::cout << "Please input a scramble\n";
		return 1;
	}
	ThistlewaiteSolver			ThistlewaiteSolver(cube, table);
	ThistlewaiteSolver.solveCube();

	std::string solution = ThistlewaiteSolver.fullSolution;
	visualizer(argc, argv, solution);

    return 0;
}
