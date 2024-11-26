#include <GL/glut.h>
#include<bits/stdc++.h>
using namespace std;

int xc,yc,r;

void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void plotCirclePoints(int x, int y) {
	// 8-way symmetry
	setPixel(xc + x, yc + y);
	setPixel(xc - x, yc + y);
	setPixel(xc + x, yc - y);
	setPixel(xc - x, yc - y);
	setPixel(xc + y, yc + x);
	setPixel(xc - y, yc + x);
	setPixel(xc + y, yc - x);
	setPixel(xc - y, yc - x);
}

void midpoint_circle() {
	int x=0,y=r;
	float p= 3-2*r;
	plotCirclePoints(x, y);
	while(x<y){
    	if(p<0){
        	p=p+4*x+6;
        	x++;
    	}
    	else{
        	p=p+4*(x-y)+10;
        	x++;
        	y--;
    	}
    	plotCirclePoints(x, y);
	}
    
	// Flush all the points to the screen at once
	glFlush();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	midpoint_circle();
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);  // Black background
	glColor3f(1.0, 1.0, 1.0);      	// White drawing color
	glPointSize(2.0);              	// Point size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);    	// Define the 2D orthographic viewing region
}

int main(int argc, char** argv) {
	printf("Enter the coordinates of center of the circle (give space in between): ");
	cin>>xc>>yc;
	printf("Enter the radius): ");
	cin>>r;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Bresenham's circle algorithm implementation");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}

