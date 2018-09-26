#include <iostream>
#include <GL/glut.h>
using namespace std;

int IterNum = 5000, Width=50, Height = 50;

// The more the iterNum is, the solider the pic is. 5000 to 100000
// The higher the width is, the shorter the pic is.
// The higher the height is, the more narrow the pic is.
// Change vertices[0][0] from 0 to 10. 图形左边定点向右移动.
// Change vertices[0][1] from 0 tp 10. 图形左边定点向上移动.
// Change vertices[1][0] from 25 to 50. 图形上边定点向右移动。
// from 25 to 0.图形上边定点向左移动.
// Change vertices[1][1] from 50 to 25. 图形上边定点向下移动.
// Change vertices[2][0] from 50 to 25. 图形右边定点向左移动。
// Change vertices[2][1] from 0 to 25. 图形右边定点向上移动。
int fuck = 0;

void myinit()
{
// attributes
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(1.0,0.0,0.0);

// set up viewing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, Width, 0.0, Height);
    glMatrixMode(GL_MODELVIEW);
}


void display() // is randomly called
{
    GLfloat vertices[3][3] = {{0.0,0.0,0.0}, {25.0, 50,0.0}, {50.0,0.0,0.0}};
// an arbitrary triangle in the plane z = 0;
    GLfloat p[3] = {7.5, 5.0, 0.0};
    // or set any desired initial point which is inside the triangle;
    int  j,k;
    int  rand();
    glBegin(GL_POINTS);
    cout<<"IterNum:"<<IterNum<<endl;
    for (k = 0; k < IterNum; k++)
    {

        /* pick a random vertex from 0, 1, 2*/
        j = rand()%3;
        // compute new location;
        p[0] = (p[0]+vertices[j][0])/2;
        p[1] = (p[1]+vertices[j][1])/2;
        // display new point
        glVertex3fv(p);
        fuck++;
        cout<<fuck<<endl;
    }
    glEnd();
    glFlush();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Simple OpenGL Example");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();

    return 0;
}