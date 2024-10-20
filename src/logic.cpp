#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include "draw.h"
#include "window.h"

double angleX = 0.0;
double angleY = 0.0;
double angleZ = 0.0;

double projectionMatrix[3][3] = {
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0}
};

double cubeVerticies[8][3] = {
    {-50.0, -50.0, -50.0}, // Bottom-left-front
    {50.0, -50.0, -50.0},  // Bottom-right-front
    {50.0, 50.0, -50.0},   // Top-right-front
    {-50.0, 50.0, -50.0},  // Top-left-front
    {-50.0, -50.0, 50.0},  // Bottom-left-back
    {50.0, -50.0, 50.0},   // Bottom-right-back
    {50.0, 50.0, 50.0},    // Top-right-back
    {-50.0, 50.0, 50.0},   // Top-left-back
};
double projected[8][3] = {
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0}
};
double rxMatrix[3][3] = {
    {1.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0}
};
double ryMatrix[3][3] = {
    {0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0}
};
double rzMatrix[3][3] = {
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 1.0}
};

void matrixCalc() {
    // Clear projected vertices
    for (int row = 0; row < 8; row++) {
        for (int i = 0; i < 3; i++) {
            projected[row][i] = 0; // Initialize projected to zero
        }
    }

    for (int row = 0; row < 8; row++) {
        // Apply rotation matrices
        double temp[3] = {0, 0, 0};

        // Apply rotation around X
        for (int i = 0; i < 3; i++) {
            temp[i] = (cubeVerticies[row][0] * rxMatrix[i][0]) +
                       (cubeVerticies[row][1] * rxMatrix[i][1]) +
                       (cubeVerticies[row][2] * rxMatrix[i][2]);
        }
        for (int i = 0; i < 3; i++) {
            cubeVerticies[row][i] = temp[i];
        }

        // Apply rotation around Y
        for (int i = 0; i < 3; i++) {
            temp[i] = (cubeVerticies[row][0] * ryMatrix[i][0]) +
                       (cubeVerticies[row][1] * ryMatrix[i][1]) +
                       (cubeVerticies[row][2] * ryMatrix[i][2]);
        }
        for (int i = 0; i < 3; i++) {
            cubeVerticies[row][i] = temp[i];
        }

        // Apply rotation around Z
        for (int i = 0; i < 3; i++) {
            temp[i] = (cubeVerticies[row][0] * rzMatrix[i][0]) +
                       (cubeVerticies[row][1] * rzMatrix[i][1]) +
                       (cubeVerticies[row][2] * rzMatrix[i][2]);
        }
        for (int i = 0; i < 3; i++) {
            cubeVerticies[row][i] = temp[i];
        }

        angleX = 0.0;
        angleY = 0.0;
        angleZ = 0.0;
        // Apply projection
        double scale = 200.0 / (200.0 + cubeVerticies[row][2]); // Adjust the scale based on Z
        projected[row][0] = cubeVerticies[row][0] * scale + 400; // Center in window width
        projected[row][1] = cubeVerticies[row][1] * scale + 300; // Center in window height
    }
}

void lineDraw() {
    
    line(projected[5][0], projected[5][1], projected[6][0], projected[6][1]);
    line(projected[5][0], projected[5][1], projected[4][0], projected[4][1]);
    line(projected[5][0], projected[5][1], projected[1][0], projected[1][1]);

    line(projected[7][0], projected[7][1], projected[6][0], projected[6][1]);
    line(projected[7][0], projected[7][1], projected[4][0], projected[4][1]);
    line(projected[7][0], projected[7][1], projected[3][0], projected[3][1]);

    line(projected[0][0], projected[0][1], projected[4][0], projected[4][1]);
    line(projected[0][0], projected[0][1], projected[1][0], projected[1][1]);
    line(projected[0][0], projected[0][1], projected[3][0], projected[3][1]);

    line(projected[2][0], projected[2][1], projected[6][0], projected[6][1]);
    line(projected[2][0], projected[2][1], projected[1][0], projected[1][1]);
    line(projected[2][0], projected[2][1], projected[3][0], projected[3][1]);
}

void renderCube() {
    rxMatrix[1][1] = cos(angleX);
    rxMatrix[1][2] = -sin(angleX);
    rxMatrix[2][1] = sin(angleX);
    rxMatrix[2][2] = cos(angleX);

    ryMatrix[0][0] = cos(angleY);
    ryMatrix[0][2] = sin(angleY);
    ryMatrix[2][0] = -sin(angleY);
    ryMatrix[2][2] = cos(angleY);

    rzMatrix[0][0] = cos(angleZ);
    rzMatrix[0][1] = -sin(angleZ);
    rzMatrix[1][0] = sin(angleZ);
    rzMatrix[1][1] = cos(angleZ);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (int row = 0; row < 8; row++) {
        //int mNew[3] = {cubeVerticies[0][0], cubeVerticies[0][1], cubeVerticies[0][2]};
        matrixCalc();
    }
    lineDraw();
}