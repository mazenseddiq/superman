#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <cstdlib>

// Global variables
int windowWidth = 800;
int windowHeight = 600;
int laneWidth = 200;
int numLanes = 3;

float playerX = windowWidth / 2;
float playerY = 50;
float playerSpeed = 5.0f;

int score = 0;

// Define an obstacle structure
struct Obstacle {
    float x;
    float y;
};

std::vector<Obstacle> obstacles;

// Function to draw a simple rectangle
void drawRectangle(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

// Function to draw the player
void drawPlayer() {
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    drawRectangle(playerX, playerY, 40.0f, 40.0f);
}

// Function to draw an obstacle
void drawObstacle(float x, float y) {
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    drawRectangle(x, y, 30.0f, 30.0f);
}

// Function to draw the score
void drawScore() {
    glColor3f(1.0f, 1.0f, 1.0f); // White color

    glRasterPos2f(10, windowHeight - 20);
    std::string scoreStr = "Score: " + std::to_string(score);
    for (char c : scoreStr) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

// Function to handle keyboard input
void keyboardHandler(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
        if (playerX > 0) {
            playerX -= laneWidth;
        }
        break;
    case 'd':
        if (playerX < (numLanes - 1) * laneWidth) {
            playerX += laneWidth;
        }
        break;
    case 27: // ASCII code for Escape key
        exit(0);
        break;
    }
}

// Function to update the game state
void updateGame(int value) {
    // Move obstacles
    for (auto& obstacle : obstacles) {
        obstacle.y -= playerSpeed;
        if (obstacle.y < 0) {
            obstacle.y = windowHeight;
            obstacle.x = rand() % (numLanes - 1) * laneWidth;
            score++;
        }

        // Check for collision
        if (playerX < obstacle.x + 30 &&
            playerX + 40 > obstacle.x &&
            playerY < obstacle.y + 30 &&
            playerY + 40 > obstacle.y) {
            std::cout << "Game Over! Score: " << score << std::endl;
            exit(0);
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateGame, 0);
}

// Function to draw the scene
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw lanes
    for (int i = 0; i < numLanes; ++i) {
        glColor3f(0.5f, 0.5f, 0.5f); // Gray color
        drawRectangle(i * laneWidth, 0, laneWidth, windowHeight);
    }

    drawPlayer();

    // Draw obstacles
    for (auto& obstacle : obstacles) {
        drawObstacle(obstacle.x, obstacle.y);
    }

    drawScore();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Subway Surfers");


    glutFullScreen();
    gluOrtho2D(0.0, 1920, 0.0, 1080);


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    

    glutDisplayFunc(drawScene);
    glutKeyboardFunc(keyboardHandler);
    glutTimerFunc(25, updateGame, 0);

    // Generate initial obstacles
    for (int i = 0; i < 5; ++i) {
        Obstacle newObstacle;
        newObstacle.x = rand() % (numLanes - 1) * laneWidth;
        newObstacle.y = rand() % windowHeight;
        obstacles.push_back(newObstacle);
    }

    glutMainLoop();

    return 0;
}
