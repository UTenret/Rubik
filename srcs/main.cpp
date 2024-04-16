#include "RubiksCube.hpp"
#include "Solver.hpp"

std::string encodeEdgeOrientationsG0(const std::string& cube);
int calculateStateIndexG0(const std::string& edgeOrientation);
#define MAX_DEPTH 9
#define G0_N_SOLUTIONS 2048
#define G1_N_SOLUTIONS 1082565

	// enum EdgePositions {
	// 	UB, UR, UF, UL,
	// 	DR, DF, DL, DB,
	// 	FR, FL, BR, BL,
	// 	EDGE_COUNT
	// };

	// const int edgeIndices[EDGE_COUNT][2] = {
	// 	{37, 19},	// UB || YG
	// 	{41, 10},	// UR || YR
	// 	{43, 1},	// UF || YB
	// 	{39, 28},	// UL || YO

	// 	{50, 16},	// DR || WR
	// 	{46, 7},	// DF || WB
	// 	{48, 34},	// DL || WO
	// 	{52, 25},	// DB || WG

	// 	{5,  12},	// FR || BR
	// 	{3,  32},	// FL || BO
	// 	{21, 14},	// BR || GR
	// 	{23, 30},	// BL || GO
	// };

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
	Solver			solver(cube, table);
	(void)argc;
	(void)argv;

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
	// if (argc > 1) {
	// 	string scramble = av[1];
    //     std::vector<std::string> moves = splitString(scramble);
	// 	for (const string& move : moves) {
    //         applyMove(cube, move);
    //     }
	// 	printCube(cube);
	// 	solveCube(cube, lutG0);
	// }
	// cout << encodeCurrentState(cube) << endl;
    return 0;
}
