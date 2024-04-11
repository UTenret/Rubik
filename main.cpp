#include "RubiksCube.hpp"
// MOVES U [UP]		U'
// MOVES D [DOWN]	D'
// MOVES R [RIGHT]	R'
// MOVES F [FRONT]	F'
// MOVES L [LEFT]	L'
// MOVES B [BACK]	B'

// ALSO 2F, 2B and so on

//
// char* [6]	center_cells;	//cannot move
// char* [24]	edge_cells;
// char* [24]	corner_cells;

std::string encodeEdgeOrientationsG0(const std::string& cube);
int calculateStateIndexG0(const std::string& edgeOrientation);
typedef std::string (*EncodeStateFunc)(const std::string&);
typedef int (*CalculateIndexFunc)(const std::string&);
void iterativeSolve(
    std::string& cube,
    const std::vector<int>& lut,
    const std::vector<std::string>& moves,
    EncodeStateFunc encodeState,
    CalculateIndexFunc calculateIndex,
    std::vector<std::string>& solution
);
#define MAX_DEPTH 9
#define G0_N_SOLUTIONS 2048
#define G1_N_SOLUTIONS 1082565

enum EdgePositions {
    UB, UR, UF, UL,
    DR, DF, DL, DB,
    FR, FL, BR, BL,
    EDGE_COUNT
};

const int edgeIndices[EDGE_COUNT][2] = {
	{37, 19},	// UB || YG
	{41, 10},	// UR || YR
	{43, 1},	// UF || YB
	{39, 28},	// UL || YO

	{50, 16},	// DR || WR
	{46, 7},	// DF || WB
	{48, 34},	// DL || WO
	{52, 25},	// DB || WG

	{5,  12},	// FR || BR
	{3,  32},	// FL || BO
	{21, 14},	// BR || GR
	{23, 30},	// BL || GO
};

/*
 U
LFR
 D
 B
*/

bool isMovePrunable(const std::string& lastMove, const std::string& currentMove) {
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

bool iddfs(std::string& cube, int depth, int maxDepth, vector<string>& solution, 
			bool (*isSolved)(std::string&), const vector<pair<void(*)(std::string&), string>>& allowedMoves) {
	// if(isSolved(cube) || isFullySolved(cube)) {
	if(isSolved(cube)){
		printCube(cube);
		cout << "SOLUTION :";
		for (const auto& move : solution) {
			cout << move << " ";
		}
		cout << endl;
		return true;
	}
	if(depth == maxDepth)
		return false;

	for (auto& [moveFunc, moveStr] : allowedMoves) {
		if (!solution.empty() && isMovePrunable(solution.back(), moveStr)) {
            continue;
        }
		moveFunc(cube);
		solution.push_back(moveStr);
		if (iddfs(cube, depth + 1, maxDepth, solution, isSolved, allowedMoves)) {
			return true;
		}
		applyInverseMove(cube, moveStr); 
		solution.pop_back();
	}
	return false;
}

vector<string> splitString(const string& str, char delimiter = ' ') {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

void solveGroup(std::string& cube, bool (*groupSolveCondition)(std::string&), const vector<pair<void(*)(std::string&), string>>& moves) {
    std::vector<string> solution;
    for (int i = 1; i < MAX_DEPTH; i++) {
        if (iddfs(cube, 0, i, solution, groupSolveCondition, moves))
            break;
    }
}

void solveCube(std::string& cube, const std::vector<int>& lut) {
	std::vector<std::string> solution;
    // vector<pair<void(*)(std::string&), string>> group0Moves = {
	// 	{moveU, "U"},
	// 	{moveUPrime, "U'"},
	// 	{moveF, "F"},
	// 	{moveFPrime, "F'"},
	// 	{moveR, "R"},
	// 	{moveRPrime, "R'"},
	// 	{moveD, "D"},
	// 	{moveDPrime, "D'"},
	// 	{moveL, "L"},
	// 	{moveLPrime, "L'"},
	// 	{moveB, "B"},
	// 	{moveBPrime, "B'"},
	// 	{moveU2, "U2"},
	// 	{moveF2, "F2"},
	// 	{moveR2, "R2"},
	// 	{moveD2, "D2"},
	// 	{moveL2, "L2"},
	// 	{moveB2, "B2"},
    // };

	std::vector<std::string> group0Moves = {
    	"U", "U'", "F", "F'", "R", "R'", "D", "D'", "L", "L'", "B", "B'", 
    	"U2", "F2", "R2", "D2", "L2", "B2"
	};

	iterativeSolve(cube, lut, group0Moves, encodeEdgeOrientationsG0, calculateStateIndexG0, solution);
    // solveGroup(cube, isGroup0Solved, group0Moves);
	// printCube(cube);
	// if (isFullySolved(cube))
		// return;
    
    vector<pair<void(*)(std::string&), string>> group1Moves = { // no F, F', B, B'
		{moveU, "U"},
		{moveUPrime, "U'"},
		{moveR, "R"},
		{moveRPrime, "R'"},
		{moveD, "D"},
		{moveDPrime, "D'"},
		{moveL, "L"},
		{moveLPrime, "L'"},
		{moveU2, "U2"},
		{moveF2, "F2"},
		{moveR2, "R2"},
		{moveD2, "D2"},
		{moveL2, "L2"},
		{moveB2, "B2"},
    };
    
    solveGroup(cube, isFullySolved, group1Moves);

}

//EDGE IS NOT FLIPPED IF WE CAN BRING IT TO ITS RIGHTFUL PLACE 
//WITHOUT F OR B (OR F' OR B')

//seems to me like the condition is the same for all up edges or down edges,
// inner cannot be white(down) or yellow(up)
// outer cannot be red(right) or orange(left) if we're considering that G1 is restricting F and B and front is blue and up yellow
// seems to me like its the same condition for literally all my edges

bool isEdgeFlipped(std::pair<char, char> colors) {
		return (colors.second == 'Y' || colors.second == 'W' || 
				colors.first == 'O' || colors.first == 'R');
}

    // we use only the first 11 edges for index calculation, as it respects the parity rule
	// removes the issue about having 4096 entry
int calculateStateIndexG0(const std::string& edgeOrientation) {
    int index = 0;
    for (size_t i = 0; i < edgeOrientation.size() - 1; ++i) {
        if (edgeOrientation[i] == '1') {
            index += (1 << i);
        }
    }
    return index;
}

std::string encodeEdgeOrientationsG0(const std::string& cube) {
    std::string orientation;
    orientation.reserve(EDGE_COUNT);
    
    for (int i = 0; i < EDGE_COUNT; ++i) {
        std::pair<char, char> edgeColors = {cube[edgeIndices[i][0]], cube[edgeIndices[i][1]]};
        bool flipped = isEdgeFlipped(edgeColors);
        
        // // Debugging output
        // std::cout << "Edge " << i << ": [" << edgeIndices[i][0] << ", " << edgeIndices[i][1] << "] "
        //           << "(" << edgeColors.first << ", " << edgeColors.second << ") "
        //           << "Flipped: " << (flipped ? "Yes" : "No") << "\n";

        if (flipped) {
            orientation.push_back('1'); // Edge is flipped
        } else {
            orientation.push_back('0'); // Edge is not flipped
        }
    }
    
    // std::cout << "Encoded Orientation: " << orientation << "\n";
    
    return orientation;
}

/*
the queue holds cube state as a string and the distance to solved
visited holds the edges orientations because we dont care about anything else for G0->G1

*/
void bfsGenerateLUTG0(const std::string& initialCube, int lut[2048]) {
    std::queue<std::pair<std::string, int>> q;
    std::set<std::string> visited;
    q.push({initialCube, 0});
    visited.insert(encodeEdgeOrientationsG0(initialCube));

    std::vector<std::string> moves = {"U", "U'", "D", "D'", "R", "R'", "L", "L'", "F", "F'", "B", "B'", "U2", "D2", "R2", "L2", "F2", "B2"};

    while (!q.empty()) {
        auto [currentState, dist] = q.front();
        q.pop();
        std::string currentEdgeOrientation = encodeEdgeOrientationsG0(currentState);
		// cout << currentState << ", " << currentState.size() << endl;
        int index = calculateStateIndexG0(currentEdgeOrientation);
		// cout << "index = " << index << endl;
        if (lut[index] == -1 || lut[index] > dist) {
            lut[index] = dist;
        }

        if (dist >= MAX_DEPTH) continue;

        for (const auto& move : moves) {
            std::string newState = currentState;
            applyMove(newState, move);

            std::string newEdgeOrientation = encodeEdgeOrientationsG0(newState);
            if (visited.insert(newEdgeOrientation).second) {
                q.push({newState, dist + 1});
            }
        }
    }
}

void iterativeSolve(
    std::string& cube,
    const std::vector<int>& lut,
    const std::vector<std::string>& moves,
    EncodeStateFunc encodeState,
    CalculateIndexFunc calculateIndex,
    std::vector<std::string>& solution
) {
    bool progress = true;

    while (progress) {
        progress = false;
        std::string currentStateEncoded = encodeState(cube);
        int currentDistance = lut[calculateIndex(currentStateEncoded)];

        if (currentDistance == 0) {
            std::cout << "Solution found: ";
            for (const auto& move : solution) std::cout << move << " ";
            std::cout << "\n";
            break;
        }

        for (const auto& move : moves) {
            std::string newState = cube;
            applyMove(newState, move);
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

std::vector<int> loadLUTG0(const std::string& filename) {
    std::vector<int> lut(2048, -1);
    std::ifstream file(filename);
    int distance;
    int index = 0;

    while (file >> distance && index < lut.size()) {
        lut[index++] = distance;
    }

    return lut;
}

int main(int argc, char* av[]) {
    // char cube[54] = {
    //     'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', // 0,  1,  2,  3   4,  5,  6,  7,  8		FRONT
    //     'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', // 9,  10, 11, 12, 13, 14, 15, 16, 17		RIGHT
    //     'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', // 18, 19, 20, 21, 22, 23, 24, 25, 26		BACK
    //     'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', // 27, 28, 29, 30, 31, 32, 33, 34, 35		LEFT
    //     'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', // 36, 37, 38, 39, 40, 41, 42, 43, 44		UP
    //     'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'	//  45, 46, 47, 48, 49, 50, 51, 52, 53		DOWN
    // };

	std::string cube = 
    "BBBBBBBBB"  // FRONT: 0 - 8
    "RRRRRRRRR"  // RIGHT: 9 - 17
    "GGGGGGGGG"  // BACK: 18 - 26
    "OOOOOOOOO"  // LEFT: 27 - 35
    "YYYYYYYYY"  // UP: 36 - 44
    "WWWWWWWWW"; // DOWN: 45 - 53

	ofstream file;
	file.open("G0.txt");
	if (!file) {
		cerr << "Error: file could not be opened";
		exit(1);
	}
	int lut[2048];
	memset(lut, -1, sizeof(lut));
	bfsGenerateLUTG0(cube, lut);
	for (int i = 0; i < 2048; i++) {
		file << lut[i] << endl;
	}
	std::vector<int> lutG0 = loadLUTG0("G0.txt");
	if (argc > 1) {
		string scramble = av[1];
        vector<string> moves = splitString(scramble);
		for (const string& move : moves) {
            applyMove(cube, move);
        }
		printCube(cube);
		solveCube(cube, lutG0);
	}
	// cout << encodeCurrentState(cube) << endl;
    return 0;
}
