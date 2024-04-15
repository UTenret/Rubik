#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <cstring>

class PruningTable {
public:
    explicit PruningTable(const std::string& initialCube);

    void generateLUT(const std::string& filename);
    std::vector<int> loadLUT(const std::string& filename);
    void solveCube(std::string& cube, const std::vector<int>& lut);

private:
    std::string initialState;
    std::vector<int> lut;

    void bfsGenerateLUT();
    bool isEdgeFlipped(const std::pair<char, char>& colors) const;
    int calculateStateIndex(const std::string& edgeOrientation) const;
    std::string encodeEdgeOrientations(const std::string& cube) const;
    std::vector<std::string> getValidMoves() const;
};
