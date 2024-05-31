#include "draw.hpp"
#include "moves.hpp"

std::string CubeState = "BBBBBBBBBRRRRRRRRRGGGGGGGGGOOOOOOOOOYYYYYYYYYWWWWWWWWW";

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

bool inFace(const std::vector<int>& faceIndices, int i) {
    return std::find(faceIndices.begin(), faceIndices.end(), i) != faceIndices.end();
}

bool inFrontFace(int i) {
    return inFace(frontFaceIndices, i);
}

bool inBackFace(int i) {
    return inFace(backFaceIndices, i);
}

bool inUpFace(int i) {
    return inFace(upFaceIndices, i);
}

bool inDownFace(int i) {
    return inFace(downFaceIndices, i);
}

bool inLeftFace(int i) {
    return inFace(leftFaceIndices, i);
}

bool inRightFace(int i) {
    return inFace(rightFaceIndices, i);
}

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

void drawFace(int animation, const std::string& CubeState) {
    if (animation == NONE)
        return;

    const std::vector<int>* faceIndices = nullptr;

    switch (animation) {
        case F_PRIME:
        case F:
            faceIndices = &frontFaceIndices;
            break;
        case U_PRIME:
        case U:
            faceIndices = &upFaceIndices;
            break;
        case B_PRIME:
        case B:
            faceIndices = &backFaceIndices;
            break;
        case D_PRIME:
        case D:
            faceIndices = &downFaceIndices;
            break;
        case L_PRIME:
        case L:
            faceIndices = &leftFaceIndices;
            break;
        case R_PRIME:
        case R:
            faceIndices = &rightFaceIndices;
            break;
        default:
            break;
    }

    if (faceIndices == nullptr)
        return;

    for (int i : *faceIndices) {
        drawCubie(i, CubeState);
    }
}
