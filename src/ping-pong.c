#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "stdint.h"
#include "unistd.h"


// 2 libraries GLAD and GLFW for OpenGL
#include "../include/glad/glad.h"  
#include "/usr/include/GLFW/glfw3.h"
#include "/usr/include/GL/gl.h"
// #include "/usr/include/GL/glu.h"
// #include "/usr/include/GL/glut.h"

// function signatures
int init();
void processInput(GLFWwindow* window, float *PADDLE_1Y, float *PADDLE_2Y, float PADDLE_SPEED);
void renderLoop(GLFWwindow* window);
void drawBall(float BALL_X, float BALL_Y);
void updateProjection(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void drawPaddle(float PADDLE_X, float PADDLE_Y);


// Window dimensions
const float WINDOW_WIDTH = 1280;
const float WINDOW_HEIGHT = 720;

// ball logic
void drawBall(float BALL_X, float BALL_Y) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

    float radius = 0.025f;
    uint numSegments = 100;  // The number of triangle segments


    glBegin(GL_TRIANGLE_FAN);
    glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
    glVertex2f(BALL_X,BALL_Y);

    for (uint i=0; i <= numSegments; i++) {
        float angle = i * (2.0f * M_PI / numSegments); // Calculate the angle for each segment
        float x = BALL_X + radius * cos(angle);
        float y = BALL_Y+ radius * sin(angle);
        glVertex2f(x, y);  // Draw the point
    }
    
    glEnd();
    glFlush();
}

// player and paddle logic
void drawPaddle(float PADDLE_X, float PADDLE_Y){
    glLoadIdentity();

    float PADDLE_HEIGHT = 0.30;
    float PADDLE_WIDTH = 0.03;

    glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    
    glVertex2f(PADDLE_X, PADDLE_Y);
    glVertex2f(PADDLE_X+PADDLE_WIDTH, PADDLE_Y);
    glVertex2f(PADDLE_X + PADDLE_WIDTH,PADDLE_Y+PADDLE_HEIGHT);
    glVertex2f(PADDLE_X, PADDLE_Y+PADDLE_HEIGHT);

    glEnd();
    glFlush();
}


// Function to initialize GLFW and GLAD
int init() {
    // Initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Ping Pong Game", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    // Make OpenGL context current
    glfwMakeContextCurrent(window);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Set OpenGL options 
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black

    // Set the initial projection
    updateProjection(window);

    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

// Function to handle window resizing and updating the projection
void updateProjection(GLFWwindow* window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);  // Set the viewport to the window size

    glMatrixMode(GL_PROJECTION);    // Switch to the projection matrix
    glLoadIdentity();               // Reset the projection matrix

    // Set the aspect ratio and projection matrix
    float aspectRatio = (float)width / (float)height;
    glOrtho(-1.0f * aspectRatio, 1.0f * aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f); // Orthographic projection
    glMatrixMode(GL_MODELVIEW);     // Switch back to modelview matrix
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
}

void processInput(GLFWwindow* window, float *PADDLE_1Y, float *PADDLE_2Y, float PADDLE_SPEED) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE); // Close the window when ESC is pressed
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (*PADDLE_2Y < 0.7f) {
            *PADDLE_2Y += PADDLE_SPEED;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (*PADDLE_2Y > -1.0f) {
            *PADDLE_2Y -= PADDLE_SPEED;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if (*PADDLE_1Y < 0.7f) {
            *PADDLE_1Y += PADDLE_SPEED;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (*PADDLE_1Y > -1.0f) {
            *PADDLE_1Y -= PADDLE_SPEED;
        }
    }
}

void renderLoop(GLFWwindow* window) {
    // Balll
    float BALL_X = 0.0f;
    float BALL_Y = 0.0f;

    float BALL_XSPEED = 0.0175f;
    float BALL_YSPEED = 0.0175f;
    const float BALL_RADIUS = 0.025f;

    // Screen
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float aspectRatio = (float)width / (float)height;
    float rightBoundary = aspectRatio;
    float leftBoundary = -aspectRatio;
    float topBoundary = 1.0f;
    float bottomBoundary = -1.0f;

     // Paddles
    float PADDLE_HEIGHT = 0.30;
    float PADDLE_WIDTH = 0.03;

    const float PADDLE_1X = -1.77f; // constant
    float PADDLE_1Y = 0.0f;

    const float PADDLE_2X = 1.74f; //constant
    float PADDLE_2Y = 0.0f;

    const float PADDLE_SPEED = 0.03f;

    // Score
    uint scoreP1 = 0;
    uint scoreP2 = 0;
    
    // fps
    float dt = 0.0f;  // Time between current frame and last frame
    float lastFrame = 0.0f;  // Time of the last frame
    glfwSwapInterval(1);  // 1 enables V-Sync, 0 disables V-Sync
    const float targetFPS = 60.0f;
    const float frameTime = 1.0f / targetFPS;  // Time per frame in seconds



    while (!glfwWindowShouldClose(window)) {
        float startTime = glfwGetTime();
        processInput(window, &PADDLE_1Y, &PADDLE_2Y, PADDLE_SPEED);
        
        // Calculate deltaTime
        float currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        BALL_X += BALL_XSPEED;
        BALL_Y += BALL_YSPEED;

        // Ball collision with paddles
        // Left Paddle
        if ((BALL_X - BALL_RADIUS <= PADDLE_1X + PADDLE_WIDTH) && (BALL_XSPEED < 0)) {
            if ((BALL_Y + BALL_RADIUS >= PADDLE_1Y) && (BALL_Y - BALL_RADIUS <= PADDLE_1Y + PADDLE_HEIGHT)) {
                BALL_XSPEED = -BALL_XSPEED;
            }
        }
        // Right Paddle
        if ((BALL_X + BALL_RADIUS >= PADDLE_2X) && (BALL_XSPEED > 0)) {
            if ((BALL_Y + BALL_RADIUS >= PADDLE_2Y) && (BALL_Y - BALL_RADIUS <= PADDLE_2Y + PADDLE_HEIGHT)) {
                BALL_XSPEED = -BALL_XSPEED;
            }
        }

        // Side boundaries (reset ball position)
        if (BALL_X + BALL_RADIUS >= rightBoundary) {
            scoreP1++;
            BALL_X = 0.0f;
            BALL_Y = 0.0f;
            BALL_XSPEED = -BALL_XSPEED;
            BALL_YSPEED = -BALL_YSPEED;
        } else if ( BALL_X - BALL_RADIUS <= leftBoundary) {
            scoreP2++;
            BALL_X = 0.0f;
            BALL_Y = 0.0f;
            BALL_XSPEED = -BALL_XSPEED;
            BALL_YSPEED = -BALL_YSPEED;
        }
        // Top boundary (bounce)
        if (BALL_Y + BALL_RADIUS >= topBoundary) {
            BALL_Y = topBoundary - BALL_RADIUS;
            BALL_YSPEED = -BALL_YSPEED;
        }
        // Bottom boundary (bounce)
        if (BALL_Y - BALL_RADIUS <= bottomBoundary) {
            BALL_Y = bottomBoundary + BALL_RADIUS;
            BALL_YSPEED = -BALL_YSPEED;
        }
        
        drawBall(BALL_X, BALL_Y);
        drawPaddle(PADDLE_1X, PADDLE_1Y);
        drawPaddle(PADDLE_2X, PADDLE_2Y);
        glfwSwapBuffers(window);
        glfwPollEvents();
        // Limit the frame rate by waiting until the next frame
        float elapsedTime = glfwGetTime() - startTime;
        if (elapsedTime < frameTime) {
            glfwWaitEventsTimeout(frameTime - elapsedTime);  // Wait for the remaining time
        }
    }
}

int main() {
    if (init() != 0) {
        return -1;
    }

    GLFWwindow* window = glfwGetCurrentContext();
    renderLoop(window);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}