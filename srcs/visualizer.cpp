#include "draw.hpp"
#include "moves.hpp"
#include "visualizer.hpp"
#include "ThistlewaiteSolver.hpp"

float rotationAngle = 0.0f;
float cameraAngle = 0.0f;
int animationActive = NONE;
float cameraX = 7.0f;
float cameraY = 7.0f;
float cameraZ = 7.0f;
bool side = UP;
std::string solution;
std::string argv;
int lines;
bool solved;

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
    drawCube(animationActive);
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
    drawFace(animationActive);
    glPopMatrix();
    
    std::string line[lines];
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < lines; i++) {
        std::string sub_text = argv.substr(i * 40, 40);
        line[i] = sub_text;

        glRasterPos2f(0.0f, 3.2f - i * 0.2f);

        for (char c : sub_text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    std::string info = "x: " + std::to_string(cameraX) + 
    " | y: " + std::to_string(cameraY) + " | z: " + std::to_string(cameraZ);
    glRasterPos2f(0.0f, 3.5f);
    for (char c : info) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

    info = "use WASD or arrows to inspect the cube";
    glRasterPos2f(0.0f, 3.8f);
    for (char c : info) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    info = "use F2 to rescramble the cube";
    glRasterPos2f(0.0f, 4.0f);
    for (char c : info) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    info = "use enter to solve the cube";
    glRasterPos2f(0.0f, 4.2f);
    for (char c : info) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);


    glutSwapBuffers();
}

void rotationF(int value) {
    (void)value;
    if (animationActive != NONE && animationActive != F) {
        glutTimerFunc(16, rotationF, 0);
        return;
    }
    rotationAngle -= 2.0f;
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
    (void)value;
    if (animationActive != NONE && animationActive != F_PRIME) {
        glutTimerFunc(16, rotationFP, 0);
        return;
    }
    rotationAngle += 2.0f;
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


void rotationB(int value) {
    (void)value;
    if (animationActive != NONE && animationActive != B) {
        glutTimerFunc(16, rotationB, 0);
        return;
    }
    rotationAngle += 2.0f;
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
    (void)value;
    if (animationActive != NONE && animationActive != B_PRIME) {
        glutTimerFunc(16, rotationBP, 0);
        return;
    }
    rotationAngle -= 2.0f;
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
    (void)value;
    if (animationActive != NONE && animationActive != U) {
        glutTimerFunc(16, rotationU, 0);
        return;
    }
    rotationAngle -= 2.0f;
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
    (void)value;
    if (animationActive != NONE && animationActive != U_PRIME) {
        glutTimerFunc(16, rotationUP, 0);
        return;
    }
    rotationAngle += 2.0f;
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
    (void)value;
    if (animationActive != NONE && animationActive != D) {
        glutTimerFunc(16, rotationD, 0);
        return;
    }
    rotationAngle += 2.0f;
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
    (void)value;
    if (animationActive != NONE && animationActive != D_PRIME) {
        glutTimerFunc(16, rotationDP, 0);
        return;
    }
    rotationAngle -= 2.0f;
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
    (void)value;
    if (animationActive != NONE && animationActive != L) {
        glutTimerFunc(16, rotationL, 0);
        return;
    }
    rotationAngle += 2.0f;
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
    (void)value;
    if (animationActive != NONE && animationActive != L_PRIME) {
        glutTimerFunc(16, rotationLP, 0);
        return;
    }
    rotationAngle -= 2.0f;
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
    (void)value;
    if (animationActive != NONE && animationActive != R) {
        glutTimerFunc(16, rotationR, 0);
        return;
    }
    rotationAngle -= 2.0f;
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
    (void)value;
    if (animationActive != NONE && animationActive != R_PRIME) {
        glutTimerFunc(16, rotationRP, 0);
        return;
    }
    rotationAngle += 2.0f;
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

void    parsing(std::string moves) {
    int i = 0;
    int delay = 900;
    int moveNum = 0;
    while (moves[i] != '\0') {
        if (moves[i] == ' ')
            i++;
        auto timerFunc = [&](void (*func)(int)) {
            glutTimerFunc(delay * moveNum++, func, 0);
        };
        if (moves[i] == 'F') {
            if (moves[i + 1] && moves[i + 1] == '2') {
                timerFunc(rotationF);
                timerFunc(rotationF);
                i++;
            } else if (moves[i + 1] && moves[i + 1] == '\'') {
                timerFunc(rotationFP);
                i++;
            } else
                timerFunc(rotationF);
            i++;
        }
        else if (moves[i] == 'B') {
            if (moves[i + 1] && moves[i + 1] == '2') {
                timerFunc(rotationB);
                timerFunc(rotationB);
                i++;
            } else if (moves[i + 1] && moves[i + 1] == '\'') {
                timerFunc(rotationBP);
                i++;
            } else
                timerFunc(rotationB);
            i++;
        }
        else if (moves[i] == 'U') {
            if (moves[i + 1] && moves[i + 1] == '2') {
                timerFunc(rotationU);
                timerFunc(rotationU);
                i++;
            } else if (moves[i + 1] && moves[i + 1] == '\'') {
                timerFunc(rotationUP);
                i++;
            } else
                timerFunc(rotationU);
            i++;
        }
        else if (moves[i] == 'D') {
            if (moves[i + 1] && moves[i + 1] == '2') {
                timerFunc(rotationD);
                timerFunc(rotationD);
                i++;
            } else if (moves[i + 1] && moves[i + 1] == '\'') {
                timerFunc(rotationDP);
                i++;
            } else
                timerFunc(rotationD);
            i++;
        }
        else if (moves[i] == 'L') {
            if (moves[i + 1] && moves[i + 1] == '2') {
                timerFunc(rotationL);
                timerFunc(rotationL);
                i++;
            } else if (moves[i + 1] && moves[i + 1] == '\'') {
                timerFunc(rotationLP);
                i++;
            } else
                timerFunc(rotationL);
            i++;
        }
        else if (moves[i] == 'R') {
            if (moves[i + 1] && moves[i + 1] == '2') {
                timerFunc(rotationR);
                timerFunc(rotationR);
                i++;
            } else if (moves[i + 1] && moves[i + 1] == '\'') {
                timerFunc(rotationRP);
                i++;
            } else
                timerFunc(rotationR);
            i++;
        }
        else {
            i++;
        }
    }
}

void    adjustCoords() {
    if (cameraX > 0) cameraX = 7.0f;
    else cameraX = -7.0f;
    if (cameraY > 0) cameraY = 7.0f;
    else cameraY = -7.0f;
    if (cameraZ > 0) cameraZ = 7.0f;
    else cameraZ = -7.0f;
}

void rotateCameraA(int value) {
    (void)value;
    
    if (animationActive != NONE && animationActive != CAM_A) {
        glutTimerFunc(16, rotateCameraA, 0);
        return;
    }

    cameraAngle += 2.0f;
    animationActive = CAM_A;
    if (cameraAngle >= 90.0f) {
        cameraAngle = 90.0f;
        animationActive = NONE;
        glutPostRedisplay();
        cameraAngle = 0.0f;
        adjustCoords();
        return;
    }
    
    float radians = (2.0f * M_PI) / 180.0f;
    float newCameraX = cameraX * cos(radians) - cameraZ * sin(radians);
    float newCameraZ = cameraX * sin(radians) + cameraZ * cos(radians);
    cameraX = newCameraX;
    cameraZ = newCameraZ;

    glutPostRedisplay();
    glutTimerFunc(16, rotateCameraA, 0);
}

void rotateCameraD(int value) {
    (void)value;

    if (animationActive != NONE && animationActive != CAM_D) {
        glutTimerFunc(16, rotateCameraD, 0);
        return;
    }

    cameraAngle += 2.0f;
    animationActive = CAM_D;
    if (cameraAngle >= 90.0f) {
        cameraAngle = 90.0f;
        animationActive = NONE;
        glutPostRedisplay();
        cameraAngle = 0.0f;
        adjustCoords();
        return;
    }

    float radians = (-2.0f * M_PI) / 180.0f;
    float newCameraX = cameraX * cos(radians) - cameraZ * sin(radians);
    float newCameraZ = cameraX * sin(radians) + cameraZ * cos(radians);
    cameraX = newCameraX;
    cameraZ = newCameraZ;

    glutPostRedisplay();
    glutTimerFunc(16, rotateCameraD, 0);
}


void rotateCameraS(int value) {
    (void)value;

    if (animationActive != NONE && animationActive != CAM_W) {
        glutTimerFunc(16, rotateCameraS, 0);
        return;
    }

    cameraAngle += 2.0f;
    animationActive = CAM_W;
    if (cameraAngle >= 90.0f) {
        side = DOWN;
        cameraAngle = 90.0f;
        animationActive = NONE;
        glutPostRedisplay();
        cameraAngle = 0.0f;
        adjustCoords();
        return;
    }

    float radians = (2.0f * M_PI) / 180.0f;
    if (cameraZ > 0) {
        float newCameraY = cameraY * cos(radians) - cameraZ * sin(radians);
        float newCameraZ = cameraY * sin(radians) + cameraZ * cos(radians);
        cameraY = newCameraY;
        cameraZ = newCameraZ;
    } else {
        float newCameraZ = cameraZ * cos(radians) - cameraY * sin(radians);
        float newCameraY = cameraZ * sin(radians) + cameraY * cos(radians);
        cameraZ = newCameraZ;
        cameraY = newCameraY;
    }

    glutPostRedisplay();
    glutTimerFunc(16, rotateCameraS, 0);
}

void rotateCameraW(int value) {
    (void)value;

    if (animationActive != NONE && animationActive != CAM_S) {
        glutTimerFunc(16, rotateCameraW, 0);
        return;
    }

    cameraAngle += 2.0f;
    animationActive = CAM_S;
    if (cameraAngle >= 90.0f) {
        side = UP;
        cameraAngle = 90.0f;
        animationActive = NONE;
        glutPostRedisplay();
        cameraAngle = 0.0f;
        adjustCoords();
        return;
    }
    float radians = (-2.0f * M_PI) / 180.0f;
    if (cameraZ > 0) {
        float newCameraY = cameraY * cos(radians) - cameraZ * sin(radians);
        float newCameraZ = cameraY * sin(radians) + cameraZ * cos(radians);
        cameraY = newCameraY;
        cameraZ = newCameraZ;
    } else {
    float newCameraZ = cameraZ * cos(radians) - cameraY * sin(radians);
    float newCameraY = cameraZ * sin(radians) + cameraY * cos(radians);
    cameraZ = newCameraZ;
    cameraY = newCameraY;
    }

    glutPostRedisplay();
    glutTimerFunc(16, rotateCameraW, 0);
}

std::string generateScramble(int length) {
    const std::vector<std::string> moves = {"R", "L", "U", "D", "F", "B"};
    const std::vector<std::string> modifiers = {"", "'", "2"};
    std::string scramble;

    srand(time(0));
    for (int i = 0; i < length; ++i) {
        std::string move = moves[rand() % moves.size()];
        std::string modifier = modifiers[rand() % modifiers.size()];
        scramble += move + modifier + " ";
    }

    return scramble;
}

void keyboard(unsigned char key, int x, int y) {
    (void)x;
    (void)y;
    if (key == 'a' || key == 'A')
        glutTimerFunc(0, rotateCameraA, 0);
    else if (key == 'd' || key == 'D')
        glutTimerFunc(0, rotateCameraD, 0);
    else if ((key == 'w' || key == 'W') && side == DOWN)
        glutTimerFunc(0, rotateCameraW, 0);
    else if ((key == 's' || key == 'S') && side == UP)
        glutTimerFunc(0, rotateCameraS, 0 );
    else if (key == 13) { //enter
        if (solved == false) {
            parsing(solution);
            solved = true;
        } else std::cout << "Cube is already solved" << std::endl;
    } else if (key == 27) //escape
        exit(0);
    glutPostRedisplay();
}

void captureUserInput(const std::string& prompt, const std::function<void(int)>& callback) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    
    try {
        int value = std::stoi(input);
        callback(value);
    } catch (std::invalid_argument& e) {
        std::cerr << "Invalid input, please enter a valid integer." << std::endl;
    }
}

void SpecialInput(int key, int x, int y) {
    (void)x;
    (void)y;
    switch(key) {
        case GLUT_KEY_UP:
            if (side == DOWN)
                glutTimerFunc(0, rotateCameraW, 0);
            break;
        case GLUT_KEY_DOWN:
            if (side == UP)
            glutTimerFunc(0, rotateCameraS, 0 );
            break;
        case GLUT_KEY_LEFT:
            glutTimerFunc(0, rotateCameraA, 0);
            break;
        case GLUT_KEY_RIGHT:
            glutTimerFunc(0, rotateCameraD, 0);
            break;
        case GLUT_KEY_F2:
            if (solved == true) {
                captureUserInput("Enter length of a scramble: ", [](int length) {
                    std::cout << "Processing..." << std::endl;
                    std::string scramble = generateScramble(length);
                    std::cout << scramble << std::endl;
                    parsing(scramble);
                    solution = rescramble(scramble);
                    solved = false;
                    std::string prefix = "scramble: ";
                    argv = prefix + scramble;
                    lines = (argv.size() / 40) + 1;
                });
            } else std::cout << "Cube is already scrambled" << std::endl;
            break;
    }
    glutPostRedisplay();
}

int visualizer(int ac, char** av, std::string fullSolution) {
    solution = fullSolution;
    if (ac > 1)
        argv = av[1];
    else
        argv = "";
    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(550, 750);
    glutInitWindowPosition(1100, 200);
    glutCreateWindow("Rubik's visualizer");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialInput);

    if (ac == 2) {
        std::string prefix = "scramble: ";
        argv = prefix + av[1];
        lines = (argv.size() / 40) + 1;
        parsing(av[1]);
        solved = false;
    }
    glutMainLoop();
    return 0;
}
