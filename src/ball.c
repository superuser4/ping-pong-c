#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "stdint.h"

// 2 libraries GLAD and GLFW for OpenGL
#include "../include/glad/glad.h"  
#include "/usr/include/GLFW/glfw3.h"
#include "/usr/include/GL/gl.h"

void drawBall() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

    // Set the circle parameters
    float centerX = 0.0f;
    float centerY = 0.0f;
    float radius = 0.025f;
    uint numSegments = 100;  // The number of triangle segments


    glBegin(GL_TRIANGLE_FAN);
    glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
    glVertex2f(centerX,centerY);

    for (uint i=0; i <= numSegments; i++) {
        float angle = i * (2.0f * M_PI / numSegments); // Calculate the angle for each segment
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x, y);  // Draw the point
    }
    
    glEnd();
    glFlush();
}
