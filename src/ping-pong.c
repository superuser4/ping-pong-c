#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "stdint.h"


// 2 libraries GLAD and GLFW for OpenGL
#include "../include/glad/glad.h"  
#include "/usr/include/GLFW/glfw3.h"
#include "/usr/include/GL/gl.h"
// #include "/usr/include/GL/glu.h"
// #include "/usr/include/GL/glut.h"

// function signatures
int init();
void processInput(GLFWwindow* window);
void renderLoop(GLFWwindow* window);
void drawBall();
void updateProjection(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void updatePaddle();
void ballReset();
void UpdateBall();
void drawPaddle(int PADDLE_X, int PADDLE_Y);


// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// ball logic
void drawBall(int BALL_X, int BALL_Y) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

    //Set the circle parameters
    // float centerX = 0.0f;
    // float centerY = 0.0f;
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
void ballReset(){}
void UpdateBall(){}

// player and paddle logic
void drawPaddle(int PADDLE_X, int PADDLE_Y){}
void updatePaddle(){}


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

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE); // Close the window when ESC is pressed
    }
}

// Main rendering loop
void renderLoop(GLFWwindow* window) {
    // ball, default numbers in the middle
    float BALL_X = 0.0f;
    float BALL_Y = 0.0f;

    int BALL_XSPEED = 5;
    int BALL_YSPEED = 5;

    // paddles
    int PADDLE_WIDTH = 10;
    int PADDLE_HEIGHT = 100;

    float PADDLE1_X = 20;
    float PADDLE1_Y = WINDOW_HEIGHT / (PADDLE_HEIGHT / 2) + 300;

    float PADDLE_2X = WINDOW_WIDTH - 30;
    float PADDLE_2Y = WINDOW_HEIGHT / (PADDLE_HEIGHT / 2) + 300;

    int PADDLE_SPEED = 5;

    while (!glfwWindowShouldClose(window)) {
        // Input processing
        processInput(window);

        drawBall(BALL_X, BALL_Y);
        // test to see if I can move the ball
        BALL_X += BALL_XSPEED;
        BALL_Y += BALL_YSPEED;

        // Swap buffers
        glfwSwapBuffers(window);
        // Poll events (for input handling)
        glfwPollEvents();
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
