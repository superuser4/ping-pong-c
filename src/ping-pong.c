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
#include "/usr/include/GL/glut.h"

// function signatures
int init();
void processInput(GLFWwindow* window, float *PADDLE_1Y, float *PADDLE_2Y, float PADDLE_SPEED);
void renderLoop(GLFWwindow* window);
void drawBall(float BALL_X, float BALL_Y);
void updateProjection(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void drawPaddle(float PADDLE_X, float PADDLE_Y);
void renderScore(int scoreP1, int scoreP2);


const float WINDOW_WIDTH = 1280;
const float WINDOW_HEIGHT = 720;


void drawBall(float BALL_X, float BALL_Y) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float radius = 0.025f;
    uint numSegments = 100;


    glBegin(GL_TRIANGLE_FAN);
    glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
    glVertex2f(BALL_X,BALL_Y);

    for (uint i=0; i <= numSegments; i++) {
        float angle = i * (2.0f * M_PI / numSegments);
        float x = BALL_X + radius * cos(angle);
        float y = BALL_Y+ radius * sin(angle);
        glVertex2f(x, y); 
    }
    
    glEnd();
    glFlush();
}


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



int init() {
  
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

  
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Ping Pong Game", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }


    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


    updateProjection(window);

    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}


void updateProjection(GLFWwindow* window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspectRatio = (float)width / (float)height;
    glOrtho(-1.0f * aspectRatio, 1.0f * aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
}

void processInput(GLFWwindow* window, float *PADDLE_1Y, float *PADDLE_2Y, float PADDLE_SPEED) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
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


void renderScore(int scoreP1, int scoreP2) {
    glColor3f(1.0f, 1.0f, 1.0f);


    glPushMatrix();
    glRasterPos2f(-0.6f, 0.9f);
    char score1[5];
    snprintf(score1, 5, "%d", scoreP1);
    for (int i = 0; score1[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, score1[i]);
    }
    glPopMatrix();


    glPushMatrix();
    glRasterPos2f(0.5f, 0.9f);
    char score2[5];
    snprintf(score2, 5, "%d", scoreP2);
    for (int i = 0; score2[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, score2[i]);
    }
    glPopMatrix();
}


void renderLoop(GLFWwindow* window) {

    float BALL_X = 0.0f;
    float BALL_Y = 0.0f;

    float BALL_XSPEED = 0.0175f;
    float BALL_YSPEED = 0.0175f;
    const float BALL_RADIUS = 0.025f;


    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float aspectRatio = (float)width / (float)height;
    float rightBoundary = aspectRatio;
    float leftBoundary = -aspectRatio;
    float topBoundary = 1.0f;
    float bottomBoundary = -1.0f;


    float PADDLE_HEIGHT = 0.30;
    float PADDLE_WIDTH = 0.03;

    const float PADDLE_1X = -1.77f;
    float PADDLE_1Y = 0.0f;

    const float PADDLE_2X = 1.74f;
    float PADDLE_2Y = 0.0f;

    const float PADDLE_SPEED = 0.03f;

    uint scoreP1 = 0;
    uint scoreP2 = 0;
    
    float dt = 0.0f;
    float lastFrame = 0.0f;
    glfwSwapInterval(1);
    const float targetFPS = 60.0f;
    const float frameTime = 1.0f / targetFPS;



    while (!glfwWindowShouldClose(window)) {
        float startTime = glfwGetTime();
        processInput(window, &PADDLE_1Y, &PADDLE_2Y, PADDLE_SPEED);
        

        float currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        BALL_X += BALL_XSPEED;
        BALL_Y += BALL_YSPEED;


        if ((BALL_X - BALL_RADIUS <= PADDLE_1X + PADDLE_WIDTH) && (BALL_XSPEED < 0)) {
            if ((BALL_Y + BALL_RADIUS >= PADDLE_1Y) && (BALL_Y - BALL_RADIUS <= PADDLE_1Y + PADDLE_HEIGHT)) {
                BALL_XSPEED = -BALL_XSPEED;
            }
        }

        if ((BALL_X + BALL_RADIUS >= PADDLE_2X) && (BALL_XSPEED > 0)) {
            if ((BALL_Y + BALL_RADIUS >= PADDLE_2Y) && (BALL_Y - BALL_RADIUS <= PADDLE_2Y + PADDLE_HEIGHT)) {
                BALL_XSPEED = -BALL_XSPEED;
            }
        }


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

        if (BALL_Y + BALL_RADIUS >= topBoundary) {
            BALL_Y = topBoundary - BALL_RADIUS;
            BALL_YSPEED = -BALL_YSPEED;
        }

        if (BALL_Y - BALL_RADIUS <= bottomBoundary) {
            BALL_Y = bottomBoundary + BALL_RADIUS;
            BALL_YSPEED = -BALL_YSPEED;
        }
        
        drawBall(BALL_X, BALL_Y);
        drawPaddle(PADDLE_1X, PADDLE_1Y);
        drawPaddle(PADDLE_2X, PADDLE_2Y);

        renderScore(scoreP1, scoreP2);

        glfwSwapBuffers(window);
        glfwPollEvents();

        float elapsedTime = glfwGetTime() - startTime;
        if (elapsedTime < frameTime) {
            glfwWaitEventsTimeout(frameTime - elapsedTime);
        }
    }
}

int main() {
    if (init() != 0) {
        return -1;
    }

    int argc = 1;
    char* argv[1] = {(char*)"Pong"};
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);


    GLFWwindow* window = glfwGetCurrentContext();
    renderLoop(window);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}