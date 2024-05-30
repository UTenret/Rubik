#pragma once

#include <GL/glut.h>
#include <string>
#include <iostream>
#include <ostream>
#include "draw.hpp"

enum AnimationState {
    NONE,
    F, F_PRIME,
    B, B_PRIME,
    R, R_PRIME,
    L, L_PRIME,
    U, U_PRIME,
    D, D_PRIME,
    CAM_A,
    CAM_D,
    CAM_W,
    CAM_S
};

#define UP true
#define DOWN false

void    updateState(int move);

