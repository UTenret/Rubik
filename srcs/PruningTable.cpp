#include "PruningTable.hpp"

PruningTable::PruningTable(const RubiksCube& cube) : cube(cube), luts{
          std::vector<int>(G0_N_SOLUTIONS, -1),
          std::vector<int>(G1_N_SOLUTIONS, -1),
          std::vector<int>(G2_N_SOLUTIONS, -1),
          std::vector<int>(G3_N_SOLUTIONS, -1)
      } {}

/*
the queue holds cube state as a string and the distance to solved
visited holds the edges orientations because we dont care about anything else for G0->G1

*/

void PruningTable::bfsGenerateLUT(std::vector<int>& lut,
									CalculateIndexFunc calculateIndex,
									const std::vector<std::string>& moves) {
	std::queue<std::pair<RubiksCube, int>> q;
	std::set<int> visited;
	RubiksCube initialCube = cube;
    int initialIndex = calculateIndex(initialCube);
	q.push({initialCube, 0});
	visited.insert(initialIndex);

	while (!q.empty()) {
        auto [currentCube, dist] = q.front();
        q.pop();

        int currentIndex = calculateIndex(currentCube);

        if (lut[currentIndex] == -1 || lut[currentIndex] < dist) {
			lut[currentIndex] = dist;
		}

        if (dist >= MAX_DEPTH) continue;

        for (const auto& move : moves) {
            RubiksCube newStateCube = currentCube;
            newStateCube.applyMove(move);

			int newIndex = calculateIndex(newStateCube);

            if (visited.insert(newIndex).second) {
                q.push({newStateCube, dist + 1});
            }
        }
    }
}

void PruningTable::generateLUT() {
	const std::vector<std::string> group0Moves = {
    	"U", "U'", "F", "F'", "R", "R'", "D", "D'", "L", "L'", "B", "B'"
	};
	const std::vector<std::string> group1Moves = {
		"U", "U'", "D", "D'", "R", "R'", "L", "L'", "F2", "B2"
	};
	const std::vector<std::string> group2Moves = {
		"U", "U'", "D", "D'", "R2", "L2", "F2", "B2"
	};
	const std::vector<std::string> group3Moves = {
		"U2", "D2", "R2", "L2", "F2", "B2"
	};

	bfsGenerateLUT(luts[0], RubiksCube::calculateStateIndexG0, group0Moves);
	bfsGenerateLUT(luts[1], RubiksCube::calculateStateIndexG1, group1Moves);
	bfsGenerateLUT(luts[2], RubiksCube::calculateStateIndexG2, group2Moves);
	bfsGenerateLUT(luts[3], RubiksCube::calculateStateIndexG3, group3Moves);

	saveLUTToFile(luts[0], "Database/Thistlewaite/G0.txt");
    saveLUTToFile(luts[1], "Database/Thistlewaite/G1.txt");
    saveLUTToFile(luts[2], "Database/Thistlewaite/G2.txt");
    saveLUTToFile(luts[3], "Database/Thistlewaite/G3.txt");
}

std::vector<int> PruningTable::loadLUTFromFile(const std::string& filename, int size) {
    std::ifstream file(filename);
    int distance;
    std::vector<int> loadedLUT(size, -1);
    unsigned long index = 0;

    while (file >> distance && index < loadedLUT.size()) {
        loadedLUT[index++] = distance;
    }

    return loadedLUT;
}

const std::vector<int>& PruningTable::getLUT(int lutNumber) const {
	if (lutNumber < 0 || lutNumber > luts.size()) {
		std::cerr << "we need an error message here\n";
		exit(1);
	}
	switch(lutNumber) {
		case 0:
			return luts[0];
			break;
		case 1:
			return luts[1];
			break;
		case 2:
			return luts[2];
			break;
		case 3:
			return luts[3];
			break;
	}
	exit(1);
}

void PruningTable::setLUT(int lutNumber, const std::vector<int>& lutData) {
    if (lutNumber < 0 || lutNumber > luts.size()) {
        throw std::out_of_range("LUT number out of range.");
    }
    if (lutNumber >= luts.size()) {
        luts.resize(lutNumber + 1);
    }
    luts[lutNumber] = lutData;
}

void PruningTable::saveLUTToFile(const std::vector<int>& lut, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: file " << filename << " could not be opened" << std::endl;
        exit(1);
    }
    for (int value : lut) {
        file << value << std::endl;
    }
}