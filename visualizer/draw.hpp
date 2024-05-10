#pragma once


#include <queue>
#include <mutex>
#include <condition_variable>
#include <time.h>
#include <thread>
#include <chrono>
#include <GL/glut.h>
#include <string>
#include <iostream>
#include <ostream>
#include "colors.hpp"

extern float translationOffset;
extern std::string CubeState;

void drawCubie(int i, const std::string& CubeState);
void drawFace(int animation, const std::string& CubeState);
void drawCube(int animation, const std::string& CubeState);
