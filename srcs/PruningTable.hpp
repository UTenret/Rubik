#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <cstring>
#include "RubiksCube.hpp"


class PruningTable {
public:
    explicit PruningTable(const RubiksCube& cube);

    void generateLUT();
    std::vector<int> loadLUT(const std::string& filename);
	const std::vector<int>& getLUT(int lutNumber) const;

private:
	RubiksCube cube;
    std::vector<int> lut0;
    std::vector<int> lut1;

    void bfsGenerateLUTG0();
    void bfsGenerateLUTG1();
};
