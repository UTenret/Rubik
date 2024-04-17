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

    void generateLUT(const std::string& filename);
    std::vector<int> loadLUT(const std::string& filename);
	const std::vector<int>& getLUT() const;

private:
	RubiksCube cube;
    std::vector<int> lut;

    void bfsGenerateLUTG0();
};
