#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std;
int xc, yc, a, b;
void setPixel(int x, int y){
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void plotEllipsePoints(int x, int y){
    setPixel(xc+x,yc+y);
    setPixel(xc+x,yc-y);
    setPixel(xc-x,yc-y);
    setPixel(xc-x,yc+y);
}

void bresenham_ellipse(){
    int x=0,y=b;
    float sqa= (a*a), sqb=(b*b);
    // Region 1:
    float p1= 2*(sqb/sqa) + 1 - 2*b;
    while(2*sqb*x<2*sqa*y){
        plotEllipsePoints(x,y);
        if(p1 < 0){
            p1=p1+2*(sqb/sqa)*(2*x+3);
            x++;
        }
        else{
            p1=p1+ 2*(sqb/sqa)*(2*x+3)-4*(y-1);
            x++;
            y--;
        }
    }
// Region 2:
    float p2= 2*sqa*(1-(((y-1)*(y-1))/sqb))-x*x - (x+1)*(x+1);

    while(y>=0){
        plotEllipsePoints(x,y);
        if(p2 < 0){
            p2=p2 - (sqa/sqb)*(4*y-6)+ (4*x+4);
            x++;
            y--;
        }
        else{
            p2=p2 - (sqa/sqb)*(4*y-6);
            y--;
        }
    glFlush();
}
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    bresenham_ellipse();
}
void reshape(int width, int height) {
    // Maintain the aspect ratio of the circles when the window is resized
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}
void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 0.0, 1.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);        // Define the 2D orthographic viewing region
}
int main(int argc, char** argv){
    cout<<"Enter the Coordinates of center of ellipse: ";
    cin>>xc>>yc;
    cout<<"Enter the length of semi major axis: ";
    cin>>a;
    cout<<"Enter the length of semi minor axis: ";
    cin>>b;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Bresenham Ellipse Drawing");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

