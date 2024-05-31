#pragma once

#include "draw.hpp"

#define UP true
#define DOWN false

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

void    updateState(int move);

