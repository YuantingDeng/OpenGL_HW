//
// Created by chawdoe on 2018/9/27.
//

#include <iostream>
#include <GL/glut.h>
#include <random>
#include <ctime>
#include <functional>

using namespace std;

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define WINDOW_TITLE "homework_1_B_3 by chawdoe"
#define WINDOW_POSITION_X 0
#define WINDOW_POSITION_Y 0
#define LINE_NUMBER 1
#define POINT_SIZE 1.0f
#define ALGORITHM "DDA" // "DDA" or "Bresenham"
//#define X1 30.0
//#define Y1 0.0
//#define X2 30.0
//#define Y2 500.0

// X must be in [0, 500]
// Y must be in [0, 500]
float x1, y1, x2, y2 = 0;

int sig_y = y2 - y1 > 0 ? 1: -1;

float deltaX = x2 - x1;
float deltaY = y2 - y1;
float dy = deltaY > 0? deltaY : -deltaY;
float dx = deltaX > 0? deltaX : -deltaX;

float d = dx > dy? dx : dy;

float xInc = (x2 - x1) / d;
float yInc = (y2 - y1) / d;

time_t startTime, endTime;

std::default_random_engine engine(time(nullptr));
uniform_int_distribution<> dis(WINDOW_POSITION_X, WINDOW_WIDTH);
auto dice = std::bind(dis, engine);


void init_parameter(){

    if(x1 < x2){
        swap(x1, x2);
        swap(y1, y2);
    }

    sig_y = y2 - y1 > 0 ? 1: -1;
    deltaX = x2 - x1;
    deltaY = y2 - y1;
    dy = deltaY > 0? deltaY : -deltaY;
    dx = deltaX > 0? deltaX : -deltaX;
    d = dx > dy? dx : dy;
    xInc = (x2 - x1) / d;
    yInc = (y2 - y1) / d;
}

void DDA(){
    glPointSize(POINT_SIZE);
    glBegin(GL_POINTS);

    for(int i = 0;i<LINE_NUMBER;i++) {

        x1 = dice();
        x2 = dice();
        y1 = dice();
        y2 = dice();
        init_parameter();

        GLfloat p[3] = {x1, y1, 0}; // start point
        glVertex3fv(p);
        for (int i = 1; i <= d; i++) {
            p[0] += xInc;
            p[1] += yInc;
            glVertex3fv(p); // the point between start point and end point
        }
        glVertex3f(x2, y2, 0);
    }// end point.
    endTime = clock();
    cout<<(endTime - startTime)<<"ms"<<endl;

    glEnd();
    glFlush();
}

void Bresenham(){
    glPointSize(POINT_SIZE);
    glBegin(GL_POINTS);

    for(int i = 0;i<LINE_NUMBER;i++){

        x1 = dice();
        x2 = dice();
        y1 = dice();
        y2 = dice();
        init_parameter();
        if(deltaX >= deltaY) {
            float e = deltaX / 2;
            while(x1 < x2){
                glVertex3f(x1, y1, 0);
                e -= dy;
                if(e < 0){
                    y1 += (1 * sig_y);
                    e += dx;
                    x1 += 1;
                }else{
                    x1 += 1;
                }
            }
        }else if(deltaY >= deltaX){
            float e = deltaY / 2;
            while(y1 < y2){
                glVertex3f(x1, y1, 0);
                e -= dx;
                if(e < 0){
                    x1 += 1;
                    e += dy;
                    y1 += (1*sig_y);
                }else{
                    y1 += (1*sig_y);
                }
            }
        }

    }

    endTime = clock();
    cout<<(endTime - startTime)<<"ms"<<endl;

    glEnd();
    glFlush();
}


int main(int *argc, char **argv)
{
    int sm = 0;
    argc = &sm;

        glutInit(argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
        glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        glutCreateWindow(WINDOW_TITLE);
        glMatrixMode(GL_PROJECTION);       // Set projection parameters.
        gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);

        startTime = clock();

        if (ALGORITHM == "DDA"){
            glutDisplayFunc(DDA);
        }else{
            glutDisplayFunc(Bresenham);
        }

        glutMainLoop();


    return 0;
}
