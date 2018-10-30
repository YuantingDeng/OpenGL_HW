#include <iostream>
#include <GL/glut.h>
#include <fstream>
using namespace std;
#define WIDTH 1000
#define HEIGHT 1200
#define NUM_OF_POINTS 20666
#define SCALE_S 0.7
#define LOOK_X 5

class Point{
public:
    float x;
    float y;
    float z;
    int len;

    Point(){
        x = 0;
        y = 0;
        z = 0;
    }


    friend Point& operator += (Point &a, const Point& b){
        a.x += b.x;
        a.y += b.y;
        a.z += b.z;
        a.len += 1;
        return a;
    }

    friend Point& operator /= (Point &a, float num){
        if(num != 0){
            a.x /= num;
            a.y /= num;
            a.z /= num;
        }
        return a;
    }

    void show(){
        cout<<"("<<x<<","<<y<<","<<z<<")"<<endl;
    }

};

Point obj_v[NUM_OF_POINTS];
Point obj_f[NUM_OF_POINTS];
Point MiddlePoint_v;
Point MiddlePoint_f;

void readObj(const string& filePath="00000.obj"){
    fstream f;
    f.open(filePath);
    string tmp;
    int i_v = 0;
    int i_f = 0;
    char type;
    while(f>>type){
        if(type == 'v') {
            f >> obj_v[i_v].x;
            f >> obj_v[i_v].y;
            f >> obj_v[i_v].z;
            MiddlePoint_v += obj_v[i_v];
            i_v++;
        }else if(type == 'f') {
            f >> obj_f[i_f].x;
            f >> obj_f[i_f].y;
            f >> obj_f[i_f].z;
            MiddlePoint_f += obj_f[i_f];
            i_f++;
        }
    }

    MiddlePoint_v /= MiddlePoint_v.len;
    MiddlePoint_f /= MiddlePoint_f.len;
    f.close();
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i = 0;i<MiddlePoint_v.len;i++) {
        glBegin(GL_POINTS);
        glVertex3f(obj_v[i].x, obj_v[i].y, obj_v[i].z);

        glEnd();
    }



    glFlush();

}
void display2(){
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i = 0;i<MiddlePoint_f.len;i++) {
        glBegin(GL_POINTS);
        glVertex3f(obj_f[i].x, obj_f[i].y, obj_f[i].z);
        glEnd();
    }
    glFlush();
}

void init(void)
{
//    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    GLfloat position[] = { 0.0, 0.0, 0.0, 1.0 }; //灯泡
    glLightfv (GL_LIGHT0, GL_POSITION, position);
}

int main(int argc, char**argv) {

    readObj();

    MiddlePoint_v.show();
//    cout<<MiddlePoint_v.len<<endl;

    glutInit(&argc, argv);


    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(WIDTH, HEIGHT);

    glutInitWindowPosition(400, 400);

    glutCreateWindow(argv[0]);

//    init();

    glTranslatef(-MiddlePoint_v.x, -MiddlePoint_v.y, -MiddlePoint_v.z); // move

    glScalef(SCALE_S, SCALE_S, SCALE_S); // scale
//    glGetFloatv();

    glutDisplayFunc(display);
    GLfloat mat[16];
    glRotatef(90, 0, 1, 0);
    glGetFloatv(GL_MODELVIEW_MATRIX, mat);
    for(int i = 0;i<16;i++){
        cout<<mat[i]<<endl;
    }
//    for(int i = 0;i<1080;i++) {
//        glRotatef(i, 0, 1, 0); // angle, x-axis, y-axis, z-axis
//    }
//    gluLookAt(1, 0, 0, 0, 0, 0, 0, 1, 0); // headx, heady, headz, centerx, centery, centerz, upx, upy, upz
//    gluPerspective(160, 0.5, 0, 100000); // angle, w:h, near_dis, far_dis

    glutMainLoop();

    return 0;
}