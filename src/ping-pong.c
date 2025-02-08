#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "stdint.h"

#include "ball.h"
#include "player.h"

// 2 libraries GLAD and GLFW for OpenGL
#include "../include/glad/glad.h"  
#include "/usr/include/GLFW/glfw3.h"
#include "/usr/include/GL/gl.h"
// #include "/usr/include/GL/glu.h"
// #include "/usr/include/GL/glut.h"

// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// function signatures
int init();
void processInput(GLFWwindow* window);
void renderLoop(GLFWwindow* window);
void drawBall();
void updateProjection(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
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
    while (!glfwWindowShouldClose(window)) {
        // Input processing
        processInput(window);

        drawBall();

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
