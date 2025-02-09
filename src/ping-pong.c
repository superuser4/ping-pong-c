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
void processInput(GLFWwindow* window);
void renderLoop(GLFWwindow* window);
void drawBall(float BALL_X, float BALL_Y);
void updateProjection(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void drawPaddle(float PADDLE_X, float PADDLE_Y);


// Window dimensions
const float WINDOW_WIDTH = 800;
const float WINDOW_HEIGHT = 600;

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
void drawPaddle(float PADDLE_X, float PADDLE_Y){}


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

void renderLoop(GLFWwindow* window) {
    float BALL_X = 0.0f;
    float BALL_Y = 0.0f;

    float BALL_XSPEED = 0.03f;
    float BALL_YSPEED = 0.03f;
    float BALL_RADIUS = 0.025f;
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);  // Get the actual window size
    float aspectRatio = (float)width / (float)height;
    
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        BALL_X += BALL_XSPEED;
        BALL_Y += BALL_YSPEED;

        // Side boundaries (reset ball position)
        if (BALL_X + BALL_RADIUS >= WINDOW_WIDTH || BALL_X - BALL_RADIUS <= 0) {
            BALL_X = 0.0f;
            BALL_Y = 0.0f;
        }
        // Top and bottom boundaries (bounce)
        if (BALL_Y + BALL_RADIUS >= WINDOW_HEIGHT) {
            BALL_Y = height - BALL_RADIUS;
            BALL_YSPEED = -BALL_YSPEED;
        }
        if (BALL_Y- BALL_RADIUS <= 0) {
            BALL_Y = BALL_RADIUS;
            BALL_YSPEED = -BALL_YSPEED;
        }
        
        drawBall(BALL_X, BALL_Y);
        glfwSwapBuffers(window);
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
