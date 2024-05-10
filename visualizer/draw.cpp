#include "draw.hpp"
#include "moves.hpp"

float translationOffset = 0.0f;
std::string CubeState = 
    "BBBBBBBBB"  // FRONT: 0 - 8
    "RRRRRRRRR"  // RIGHT: 9 - 17
    "GGGGGGGGG"  // BACK: 18 - 26
    "OOOOOOOOO"  // LEFT: 27 - 35
    "YYYYYYYYY"  // UP: 36 - 44
    "WWWWWWWWW"; // DOWN: 45 - 53

#include <string>

void    colorize(int index) {
    if (CubeState[index] == 'B')
        glColor3fv(blue);
    else if (CubeState[index] == 'R')
        glColor3fv(red);
    else if (CubeState[index] == 'G')
        glColor3fv(green);
    else if (CubeState[index] == 'W')
        glColor3fv(white);
    else if (CubeState[index] == 'Y')
        glColor3fv(yellow);
    else if (CubeState[index] == 'O')
        glColor3fv(orange);
}

void drawCubie(int index, const std::string& CubeState) {
    static const float initialPositions[54][3] = {
        {-1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}, {1.0, 1.0, 1.0},
        {-1.0, 0.0, 1.0},  {0.0, 0.0, 1.0},  {1.0, 0.0, 1.0},
        {-1.0, -1.0, 1.0},  {0.0, -1.0, 1.0},  {1.0, -1.0, 1.0},

        {1.0, -1.0, -1.0},  {1.0, -1.0, 0.0},  {1.0, -1.0, 1.0},
        {1.0, 0.0, -1.0},   {1.0, 0.0, 0.0},   {1.0, 0.0, 1.0},
        {1.0, 1.0, -1.0},   {1.0, 1.0, 0.0},   {1.0, 1.0, 1.0},

        {-1.0, 1.0, -1.0}, {0.0, 1.0, -1.0}, {1.0, 1.0, -1.0},
        {-1.0, 0.0, -1.0},  {0.0, 0.0, -1.0},  {1.0, 0.0, -1.0},
        {-1.0, -1.0, -1.0},  {0.0, -1.0, -1.0},  {1.0, -1.0, -1.0},

        {-1.0, -1.0, -1.0},  {-1.0, -1.0, 0.0},  {-1.0, -1.0, 1.0},
        {-1.0, 0.0, -1.0},   {-1.0, 0.0, 0.0},   {-1.0, 0.0, 1.0},
        {-1.0, 1.0, -1.0},   {-1.0, 1.0, 0.0},   {-1.0, 1.0, 1.0},

        {1.0, 1.0, 1.0},  {1.0, 1.0, 0.0},  {1.0, 1.0, -1.0},
        {0.0, 1.0, 1.0},   {0.0, 1.0, 0.0},   {0.0, 1.0, -1.0},
        {-1.0, 1.0, 1.0},   {-1.0, 1.0, 0.0},   {-1.0, 1.0, -1.0},

        {1.0, -1.0, 1.0},  {1.0, -1.0, 0.0},  {1.0, -1.0, -1.0},
        {0.0, -1.0, 1.0},   {0.0, -1.0, 0.0},   {0.0, -1.0, -1.0},
        {-1.0, -1.0, 1.0},   {-1.0, -1.0, 0.0},   {-1.0, -1.0, -1.0}
    };

    glPushMatrix();

    // Translate to the initial position of the cubie
    glTranslatef(initialPositions[index][0], initialPositions[index][1], initialPositions[index][2]);

    // Draw the cubie
    glBegin(GL_QUADS);
    // Front face
    if (index >= 0 && index <= 8) {
        colorize(index);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
    }
    // Right face
    else if (index >= 9 && index <= 17) {
        colorize(index);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
    }
    // Back face
    else if (index >= 18 && index <= 26) {
        colorize(index);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, -0.5, -0.5);
    }
    // Left face
    else if (index >= 27 && index <= 35) {
        colorize(index);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, -0.5);
    }
    // Top face
    else if (index >= 36 && index <= 44) {
        colorize(index);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, -0.5);
    }
    // Bottom face
    else if (index >= 45 && index <= 53) {
        colorize(index);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(-0.5, -0.5, 0.5);
    }
    glEnd();

    glPopMatrix();
}

bool    inFrontFace(int i) {
    return ((i >= 0 && i <= 8) || i == 36 || i == 39 ||
    i == 42 || i == 11 || i == 14 || i == 17 || i == 29 ||
    i == 32 || i == 35 || i == 45 || i == 48 || i == 51);
}

bool    inBackFace(int i) {
    return ((i >= 18 && i <= 26) || i == 9 || i == 12 ||
    i == 15 || i == 47 || i == 50 || i == 53 || i == 38 ||
    i == 41 || i == 44 || i == 27 || i == 30 || i == 33);
}

bool    inUpFace(int i) {
    return ((i >= 36 && i <= 44) || i == 0 || i == 1 ||
    i == 2 || i == 15 || i == 16 || i == 17 || i == 18 ||
    i == 19 || i == 20 || i == 33 || i == 34 || i == 35);
}


bool    inDownFace(int i) {
    return ((i >= 45 && i <= 53) || i == 6 || i == 7 ||
    i == 8 || i == 9 || i == 10 || i == 11 || i == 24 ||
    i == 25 || i == 26 || i == 27 || i == 28 || i == 29);
}

bool    inLeftFace(int i) {
    return ((i >= 27 && i <= 35) || i == 0 || i == 3 ||
    i == 6 || i == 18 || i == 21 || i == 24 || i == 42 ||
    i == 43 || i == 44 || i == 51 || i == 52 || i == 53);
}

bool    inRightFace(int i) {
    return ((i >= 9 && i <= 17) || i == 2 || i == 5 ||
    i == 8 || i == 20 || i == 23 || i == 26 || i == 36 ||
    i == 37 || i == 38 || i == 45 || i == 46 || i == 47);
}

//update this shit
void drawCube(int animat, const std::string& CubeState) {
    for (int i = 0; i < 54; ++i) {
        if (((animat == F || animat == F_PRIME) && inFrontFace(i)) ||
        ((animat == U || animat == U_PRIME) && inUpFace(i)) ||
        ((animat == D || animat == D_PRIME) && inDownFace(i)) ||
        ((animat == L || animat == L_PRIME) && inLeftFace(i)) ||
        ((animat == R || animat == R_PRIME) && inRightFace(i)) ||
        ((animat == B || animat == B_PRIME) && inBackFace(i)))
            continue;
        drawCubie(i, CubeState);
    }
}

//update this shit
void drawFace(int animation, const std::string& CubeState) {
    if (animation == NONE)
        return;
    if (animation == F_PRIME || animation == F) {
        for (int i = 0; i < 9; i++)
            drawCubie(i, CubeState);

        drawCubie(36, CubeState);
        drawCubie(39, CubeState);
        drawCubie(42, CubeState);

        drawCubie(11, CubeState);
        drawCubie(14, CubeState);
        drawCubie(17, CubeState);

        drawCubie(29, CubeState);
        drawCubie(32, CubeState);
        drawCubie(35, CubeState);

        drawCubie(45, CubeState);
        drawCubie(48, CubeState);
        drawCubie(51, CubeState);
    }
    else if (animation == U || animation == U_PRIME) {
        for (int i = 36; i < 45; i++)
            drawCubie(i, CubeState);

        drawCubie(0, CubeState);
        drawCubie(1, CubeState);
        drawCubie(2, CubeState);

        drawCubie(15, CubeState);
        drawCubie(16, CubeState);
        drawCubie(17, CubeState);

        drawCubie(18, CubeState);
        drawCubie(19, CubeState);
        drawCubie(20, CubeState);

        drawCubie(33, CubeState);
        drawCubie(34, CubeState);
        drawCubie(35, CubeState);
    }
    else if (animation == B || animation == B_PRIME) {
        for (int i = 18; i < 27; i++)
            drawCubie(i, CubeState);

        drawCubie(9, CubeState);
        drawCubie(12, CubeState);
        drawCubie(15, CubeState);

        drawCubie(27, CubeState);
        drawCubie(30, CubeState);
        drawCubie(33, CubeState);

        drawCubie(38, CubeState);
        drawCubie(41, CubeState);
        drawCubie(44, CubeState);

        drawCubie(47, CubeState);
        drawCubie(50, CubeState);
        drawCubie(53, CubeState);
    }
    else if (animation == D || animation == D_PRIME) {
        for (int i = 45; i < 54; i++)
            drawCubie(i, CubeState);

        drawCubie(6, CubeState);
        drawCubie(7, CubeState);
        drawCubie(8, CubeState);

        drawCubie(9, CubeState);
        drawCubie(10, CubeState);
        drawCubie(11, CubeState);

        drawCubie(24, CubeState);
        drawCubie(25, CubeState);
        drawCubie(26, CubeState);

        drawCubie(27, CubeState);
        drawCubie(28, CubeState);
        drawCubie(29, CubeState);
    }
    else if (animation == L || animation == L_PRIME) {
        for (int i = 27; i < 36; i++)
            drawCubie(i, CubeState);

        drawCubie(0, CubeState);
        drawCubie(3, CubeState);
        drawCubie(6, CubeState);

        drawCubie(18, CubeState);
        drawCubie(21, CubeState);
        drawCubie(24, CubeState);

        drawCubie(42, CubeState);
        drawCubie(43, CubeState);
        drawCubie(44, CubeState);

        drawCubie(51, CubeState);
        drawCubie(52, CubeState);
        drawCubie(53, CubeState);
    }
    else if (animation == R || animation == R_PRIME) {
        for (int i = 9; i < 18; i++)
            drawCubie(i, CubeState);

        drawCubie(2, CubeState);
        drawCubie(5, CubeState);
        drawCubie(8, CubeState);

        drawCubie(20, CubeState);
        drawCubie(23, CubeState);
        drawCubie(26, CubeState);

        drawCubie(36, CubeState);
        drawCubie(37, CubeState);
        drawCubie(38, CubeState);

        drawCubie(45, CubeState);
        drawCubie(46, CubeState);
        drawCubie(47, CubeState);
    }
}
