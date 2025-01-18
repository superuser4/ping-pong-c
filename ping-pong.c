#include "stdio.h"
#include "stdlib.h"

#include </usr/include/glad/glad.h> 
#include </usr/include/GLFW/glfw3.h>
#include "/usr/include/GL/gl.h"
#include "/usr/include/GL/glu.h"
#include "/usr/include/GL/glut.h"



int main(void) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
}