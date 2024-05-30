#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <cstring>
#include <functional>
#include "RubiksCube.hpp"


class PruningTable {
public:
    explicit PruningTable(const RubiksCube& cube);

	using CalculateIndexFunc = std::function<int(const RubiksCube&)>;

	void bfsGenerateLUT(std::vector<int>& lut,
						CalculateIndexFunc calculateIndex,
						const std::vector<std::string>& moves);

    void generateLUT();
    std::vector<int> loadLUT(const std::string& filename, int size);
	const std::vector<int>& getLUT(int lutNumber) const;
	void setLUT(int lutNumber, const std::vector<int>& lutData);

private:
	RubiksCube cube;
	std::vector<std::vector<int>> luts;

};
