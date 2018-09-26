#include <iostream>
#include <GL/glut.h>
using namespace std;
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define WINDOW_TITLE "homework_1_B_3 by chawdoe"
#define WINDOW_POSITION_X 0
#define WINDOW_POSITION_Y 0
#define X1 50.0
#define Y1 0.0
#define X2 50.0
#define Y2 0.0
// X must be in [0, 500]
// Y must be in [0, 500]
float x1 = X1, y1 = Y1;
float x2 = X2, y2 = Y2;
void DDA(){
    glBegin(GL_POINTS);
    float deltaX = x2 - x1 > 0 ? x2 - x1 : x1 - x2;
    float deltaY = y2 - y1 > 0 ? y2 - y1 : y1 - y2;
    float d = deltaX > deltaY? deltaX : deltaY;
    float xInc = (x2-x1)/d;
    float yInc = (y2-y1)/d;
    GLfloat p[3] = {x1, y1, 0}; // start point
    glVertex3fv(p);
    for(int i=1;i<=d;i++){
        p[0] += xInc;
        p[1] += yInc;
        glVertex3fv(p); // the point between start point and end point
    }
    glVertex3f(x2, y2, 0); // end point
    glEnd();
    glFlush();
}
void Bresenham(){
    glBegin(GL_POINTS);
    float deltaX = x2 - x1;
    float deltaY = y2 - y1;
    if(deltaX >= deltaY) {
//        float k = deltaY/ deltaX;
        float e = deltaX / 2;
        while(x1 < x2){
            glVertex3f(x1, y1, 0);
            e -= deltaY;
            if(e < 0){
                y1 += 1;
                e += deltaX;
                x1 += 1;
            }else{
                x1 += 1;
            }
        }
    }else if(deltaY >= deltaX){
        float e = deltaY / 2;
        while(y1 < y2){
            glVertex3f(x1, y1, 0);
            e -= deltaX;
            if(e < 0){
                x1 += 1;
                e += deltaY;
                y1 += 1;
            }else{
                y1 += 1;
            }
        }
    }
    glEnd();
    glFlush();
}
int main(int *argc, char **argv)
{
    int sm = 0;
    argc = &sm;
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_TITLE);
    glMatrixMode (GL_PROJECTION);       // Set projection parameters.
    gluOrtho2D (0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
    glutDisplayFunc(Bresenham);
    glutMainLoop();
    return 0;
}
