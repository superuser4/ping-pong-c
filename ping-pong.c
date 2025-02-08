#include "stdio.h"
#include "stdlib.h"

#include "glad/glad.h"  
#include "/usr/include/GLFW/glfw3.h"
#include "/usr/include/GL/gl.h"
// #include "/usr/include/GL/glu.h"
// #include "/usr/include/GL/glut.h"

// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

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

    // Set OpenGL options (e.g., enable depth testing, etc.)
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black

    return 0;
}

// Function to handle input (optional, modify later for actual game logic)
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

        // Rendering commands
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

        // Placeholder for rendering (e.g., drawing paddles and ball here)
        // Example: Draw a simple rectangle (paddle or ball placeholder)
        glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0f); // Red color for the placeholder
            glVertex2f(-0.1f, -0.1f);
            glVertex2f( 0.1f, -0.1f);
            glVertex2f( 0.1f,  0.1f);
            glVertex2f(-0.1f,  0.1f);
        glEnd();

        // Swap buffers
        glfwSwapBuffers(window);

        // Poll events (for input handling)
        glfwPollEvents();
    }
}

int main() {
    // Initialize GLFW and GLAD
    if (init() != 0) {
        return -1;
    }

    // Create GLFW window and run rendering loop
    GLFWwindow* window = glfwGetCurrentContext();
    renderLoop(window);

    // Clean up and close
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
