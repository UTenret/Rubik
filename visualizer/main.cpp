#include "colors.hpp"
#include "draw.hpp"
#include "moves.hpp"

float rotationAngle = 0.0f;
int animationActive = NONE;
float cameraX = 5.0f;
float cameraY = 5.0f;
float cameraZ = 10.0f;

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (double)w / (double)h, 1, 100);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //camera left-right back-front up-down
    gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);

    glPushMatrix();
    drawCube(animationActive, CubeState);
    glPopMatrix();

    glPushMatrix();
    if (animationActive == F || animationActive == F_PRIME ||
    animationActive == B || animationActive == B_PRIME)
        glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
    else if (animationActive == U || animationActive == U_PRIME ||
    animationActive == D || animationActive == D_PRIME)
        glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
    else if (animationActive == L || animationActive == L_PRIME ||
    animationActive == R || animationActive == R_PRIME)
        glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);
    drawFace(animationActive, CubeState);
    glPopMatrix();

    glutSwapBuffers();
}

void rotationF(int delay) {
    if (animationActive != NONE && animationActive != F) {
        glutTimerFunc((16 * delay), rotationF, 0);
        return;
    }
    rotationAngle -= 1.0f;
    animationActive = F;
    if (rotationAngle <= -90.0f) {
        rotationAngle = 0.0f;
        glutPostRedisplay();
        animationActive = NONE;
        updateState(F);
        return;
    }
    glutPostRedisplay();
    glutTimerFunc(16, rotationF, 0);
}

void rotationFP(int value) {
    if (animationActive != NONE && animationActive != F_PRIME) {
        glutTimerFunc(16, rotationFP, 0);
        return;
    }
    rotationAngle += 1.0f;
    animationActive = F_PRIME;
    if (rotationAngle >= 90.0f) {
        rotationAngle = 0.0f;
        glutPostRedisplay();
        animationActive = NONE;
        updateState(F_PRIME);
        return;
    }
    glutPostRedisplay();
    glutTimerFunc(16, rotationFP, 0);
}


void rotationB(int delay) {
    // std::cout << "delay is " << delay << std::endl;
    if (animationActive != NONE && animationActive != B) {
        glutTimerFunc((16 * delay), rotationB, 0);
        return;
    }
    rotationAngle += 1.0f;
    animationActive = B;
    if (rotationAngle >= 90.0f) {
        rotationAngle = 0.0f;
        glutPostRedisplay();
        animationActive = NONE;
        updateState(B);
        return;
    }
    glutPostRedisplay();
    glutTimerFunc(16, rotationB, 0);
}

void rotationBP(int value) {
    if (animationActive != NONE && animationActive != B_PRIME) {
        glutTimerFunc(16, rotationBP, 0);
        return;
    }
    rotationAngle -= 1.0f;
    animationActive = B_PRIME;
    if (rotationAngle <= -90.0f) {
        rotationAngle = 0.0f;
        glutPostRedisplay();
        animationActive = NONE;
        updateState(B_PRIME);
        return;
    }
    glutPostRedisplay();
    glutTimerFunc(16, rotationBP, 0);
}

void rotationU(int value) {
    if (animationActive != NONE && animationActive != U) {
        glutTimerFunc(16, rotationU, 0);
        return;
    }
    rotationAngle -= 1.0f;
    animationActive = U;
    if (rotationAngle <= -90.0f) {
        rotationAngle = 0.0f;
        glutPostRedisplay();
        animationActive = NONE;
        updateState(U);
        return;
    }
    glutPostRedisplay();
    glutTimerFunc(16, rotationU, 0);
}

void rotationUP(int value) {
    if (animationActive != NONE && animationActive != U_PRIME) {
        glutTimerFunc(16, rotationUP, 0);
        return;
    }
    rotationAngle += 1.0f;
    animationActive = U_PRIME;
    if (rotationAngle >= 90.0f) {
        rotationAngle = 0.0f;
        glutPostRedisplay();
        animationActive = NONE;
        updateState(U_PRIME);
        return;
    }
    glutPostRedisplay();
    glutTimerFunc(16, rotationUP, 0);
}

void rotationD(int value) {
    if (animationActive != NONE && animationActive != D) {
        glutTimerFunc(16, rotationD, 0);
        return;
    }
    rotationAngle += 1.0f;
    animationActive = D;
    if (rotationAngle >= 90.0f) {
        rotationAngle = 0.0f;
        glutPostRedisplay();
        animationActive = NONE;
        updateState(D);
        return;
    }
    glutPostRedisplay();
    glutTimerFunc(16, rotationD, 0);
}

void rotationDP(int value) {
    if (animationActive != NONE && animationActive != D_PRIME) {
        glutTimerFunc(16, rotationDP, 0);
        return;
    }
    rotationAngle -= 1.0f;
    animationActive = D_PRIME;
    if (rotationAngle <= -90.0f) {
        rotationAngle = 0.0f;
        glutPostRedisplay();
        animationActive = NONE;
        updateState(D_PRIME);
        return;
    }
    glutPostRedisplay();
    glutTimerFunc(16, rotationDP, 0);
}

void rotationL(int value) {
    if (animationActive != NONE && animationActive != L) {
        glutTimerFunc(16, rotationL, 0);
        return;
    }
    rotationAngle += 1.0f;
    animationActive = L;
    if (rotationAngle >= 90.0f) {
        rotationAngle = 0.0f;
        glutPostRedisplay();
        animationActive = NONE;
        updateState(L);
        return;
    }
    glutPostRedisplay();
    glutTimerFunc(16, rotationL, 0);
}

void rotationLP(int value) {
    if (animationActive != NONE && animationActive != L_PRIME) {
        glutTimerFunc(16, rotationLP, 0);
        return;
    }
    rotationAngle -= 1.0f;
    animationActive = L_PRIME;
    if (rotationAngle <= -90.0f) {
        rotationAngle = 0.0f;
        glutPostRedisplay();
        animationActive = NONE;
        updateState(L_PRIME);
        return;
    }
    glutPostRedisplay();
    glutTimerFunc(16, rotationLP, 0);
}

void rotationR(int value) {
    if (animationActive != NONE && animationActive != R) {
        glutTimerFunc(16, rotationR, 0);
        return;
    }
    rotationAngle -= 1.0f;
    animationActive = R;
    if (rotationAngle <= -90.0f) {
        rotationAngle = 0.0f;
        glutPostRedisplay();
        animationActive = NONE;
        updateState(R);
        return;
    }
    glutPostRedisplay();
    glutTimerFunc(16, rotationR, 0);
}

void rotationRP(int value) {
    if (animationActive != NONE && animationActive != R_PRIME) {
        glutTimerFunc(16, rotationRP, 0);
        return;
    }
    rotationAngle += 1.0f;
    animationActive = R_PRIME;
    if (rotationAngle >= 90.0f) {
        rotationAngle = 0.0f;
        glutPostRedisplay();
        animationActive = NONE;
        updateState(R_PRIME);
        return;
    }
    glutPostRedisplay();
    glutTimerFunc(16, rotationRP, 0);
}

void delay(float secs)
{
	float end = clock()/CLOCKS_PER_SEC + secs;
	while((clock()/CLOCKS_PER_SEC) < end);
}

void    parsing(char *moves) {
    int i = 0;
    int delay = 2000;
    int moveNum = 0;
    while (moves[i] != '\0') {
        if (moves[i] == ' ') {
            i++;
            continue;
        }
        if (moves[i] == 'F') {
            if (moves[i + 1] && moves[i + 1] == '2') {
                glutTimerFunc((delay * moveNum++), rotationF, 0);
                glutTimerFunc((delay * moveNum++), rotationF, 0);
                i += 2;
            } else if (moves[i + 1] && moves[i + 1] == '\'') {
                glutTimerFunc((delay * moveNum++), rotationFP, 0);
                i += 2;
            } else {
                glutTimerFunc((delay * moveNum++), rotationF, 0);
                i++;
            }
        }
        else if (moves[i] == 'B') {
            if (moves[i + 1] && moves[i + 1] == '2') {
                glutTimerFunc((delay * moveNum++), rotationB, 0);
                glutTimerFunc((delay * moveNum++), rotationB, 0);
                i += 2;
            } else if (moves[i + 1] && moves[i + 1] == '\'') {
                glutTimerFunc((delay * moveNum++), rotationBP, 0);
                i += 2;
            } else {
                glutTimerFunc((delay * moveNum++), rotationB, 0);
                i++;
            }
        }
        else if (moves[i] == 'U') {
            if (moves[i + 1] && moves[i + 1] == '2') {
                glutTimerFunc((delay * moveNum++), rotationU, 0);
                glutTimerFunc((delay * moveNum++), rotationU, 0);
                i += 2;
            } else if (moves[i + 1] && moves[i + 1] == '\'') {
                glutTimerFunc((delay * moveNum++), rotationUP, 0);
                i += 2;
            } else {
                glutTimerFunc((delay * moveNum++), rotationU, 0);
                i++;
            }
        }
        else if (moves[i] == 'D') {
            if (moves[i + 1] && moves[i + 1] == '2') {
                glutTimerFunc((delay * moveNum++), rotationD, 0);
                glutTimerFunc((delay * moveNum++), rotationD, 0);
                i += 2;
            } else if (moves[i + 1] && moves[i + 1] == '\'') {
                glutTimerFunc((delay * moveNum++), rotationDP, 0);
                i += 2;
            } else {
                glutTimerFunc((delay * moveNum++), rotationD, 0);
                i++;
            }
        }
        else if (moves[i] == 'L') {
            if (moves[i + 1] && moves[i + 1] == '2') {
                glutTimerFunc((delay * moveNum++), rotationL, 0);
                glutTimerFunc((delay * moveNum++), rotationL, 0);
                i += 2;
            } else if (moves[i + 1] && moves[i + 1] == '\'') {
                glutTimerFunc((delay * moveNum++), rotationLP, 0);
                i += 2;
            } else {
                glutTimerFunc((delay * moveNum++), rotationL, 0);
                i++;
            }
        }
        else if (moves[i] == 'R') {
            if (moves[i + 1] && moves[i + 1] == '2') {
                glutTimerFunc((delay * moveNum++), rotationR, 0);
                glutTimerFunc((delay * moveNum++), rotationR, 0);
                i += 2;
            } else if (moves[i + 1] && moves[i + 1] == '\'') {
                glutTimerFunc((delay * moveNum++), rotationRP, 0);
                i += 2;
            } else {
                glutTimerFunc((delay * moveNum++), rotationR, 0);
                i++;
            }
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'a' || key == 'A') {
        cameraX--;
    }
    else if (key == 'd' || key == 'D') {
        cameraX++;
    }
    else if (key == 'w' || key == 'W') {
        cameraY++;
    }
    else if (key == 's' || key == 'S') {
        cameraY--;
    }
    else if (key == 'q' || key == 'Q') {
        cameraZ++;
    }
    else if (key == 'e' || key == 'E') {
        cameraZ--;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rubik-Huiubik");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    if (argc != 2)
        std::cerr << "Enter moves sequence\n";
    else
        parsing(argv[1]);
    glutMainLoop();
    return 0;
}
