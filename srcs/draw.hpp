#pragma once

#include <queue>
#include <iostream>
#include <ostream>
#include <algorithm>
#include <cmath>
#include <functional>
#include <GL/glut.h>

const GLfloat red[] = {0.9, 0.1, 0.1};
const GLfloat green[] = {0.0, 0.8, 0.0};
const GLfloat blue[] = {0.1, 0.1, 1.0};
const GLfloat yellow[] = {1.0, 1.0, 0.0};
const GLfloat orange[] = {1.0, 0.5, 0.0};
const GLfloat white[] = {1, 1, 1};

const std::vector<int> frontFaceIndices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 11, 14, 17, 29, 32, 35, 36, 39, 42, 45, 48, 51};
const std::vector<int> backFaceIndices = {9, 12, 15, 47, 50, 53, 38, 41, 44, 27, 30, 33, 18, 19, 20, 21, 22, 23, 24, 25, 26};
const std::vector<int> upFaceIndices = {36, 37, 38, 39, 40, 41, 42, 43, 44, 0, 1, 2, 15, 16, 17, 18, 19, 20, 33, 34, 35};
const std::vector<int> downFaceIndices = {45, 46, 47, 48, 49, 50, 51, 52, 53, 6, 7, 8, 9, 10, 11, 24, 25, 26, 27, 28, 29};
const std::vector<int> leftFaceIndices = {27, 28, 29, 30, 31, 32, 33, 34, 35, 0, 3, 6, 18, 21, 24, 42, 43, 44, 51, 52, 53};
const std::vector<int> rightFaceIndices = {9, 10, 11, 12, 13, 14, 15, 16, 17, 2, 5, 8, 20, 23, 26, 36, 37, 38, 45, 46, 47};

extern std::string CubeState;

void drawCubie(int i);
void drawFace(int animation);
void drawCube(int animation);
