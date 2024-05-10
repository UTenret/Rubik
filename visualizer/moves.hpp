#pragma once

#include <GL/glut.h>
#include <string>
#include <iostream>
#include <ostream>
#include "draw.hpp"

#define NONE 0
#define F 1
#define F_PRIME 2
#define B 3
#define B_PRIME 4
#define R 5
#define R_PRIME 6
#define L 7
#define L_PRIME 8
#define U 9
#define U_PRIME 10
#define D 11
#define D_PRIME 12

void    updateState(int move);

