#include "RubiksCube.hpp"
#include "Solver.hpp"

/*
 U
LFR
 D
 B
*/

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

//EDGE IS NOT FLIPPED IF WE CAN BRING IT TO ITS RIGHTFUL PLACE 
//WITHOUT F OR B (OR F' OR B')

//seems to me like the condition is the same for all up edges or down edges,
// inner cannot be white(down) or yellow(up)
// outer cannot be red(right) or orange(left) if we're considering that G1 is restricting F and B and front is blue and up yellow
// seems to me like its the same condition for literally all my edges


    // we use only the first 11 edges for index calculation, as it respects the parity rule
	// removes the issue about having 4096 entry


int main(int argc, char* argv[]) {
    // char cube[54] = {
    //     'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', // 0,  1,  2,  3   4,  5,  6,  7,  8		FRONT
    //     'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', // 9,  10, 11, 12, 13, 14, 15, 16, 17		RIGHT
    //     'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', // 18, 19, 20, 21, 22, 23, 24, 25, 26		BACK
    //     'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', // 27, 28, 29, 30, 31, 32, 33, 34, 35		LEFT
    //     'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', // 36, 37, 38, 39, 40, 41, 42, 43, 44		UP
    //     'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'	//  45, 46, 47, 48, 49, 50, 51, 52, 53		DOWN
    // };

	std::string initialState = 
    "BBBBBBBBB"  // FRONT: 0 - 8
    "RRRRRRRRR"  // RIGHT: 9 - 17
    "GGGGGGGGG"  // BACK: 18 - 26
    "OOOOOOOOO"  // LEFT: 27 - 35
    "YYYYYYYYY"  // UP: 36 - 44
    "WWWWWWWWW"; // DOWN: 45 - 53

	RubiksCube		cube(initialState);
	PruningTable	table(cube);
	if (argc > 1) {
		std::string scramble = argv[1];
		cube.scramble(argv[1]);
		cube.printCube();
	}
	else {
		std::cout << "Please input a scramble\n";
		return 1;
	}
	table.generateLUT("G0.txt");

	Solver			solver(cube, table);
	solver.solveCube();

	// std::ofstream file;
	// file.open("G0.txt");
	// if (!file) {
	// 	std::cerr << "Error: file could not be opened";
	// 	exit(1);
	// }
	// int lut[2048];
	// memset(lut, -1, sizeof(lut));
	// bfsGenerateLUTG0(cube, lut);
	// for (int i = 0; i < 2048; i++) {
	// 	file << lut[i] << std::endl;
	// }
	// std::vector<int> lutG0 = loadLUTG0("G0.txt");

	// cout << encodeCurrentState(cube) << endl;
    return 0;
}
