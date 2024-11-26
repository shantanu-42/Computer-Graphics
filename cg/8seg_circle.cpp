#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

int xc, yc, r;

void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void dda(int x1, int x2, int y1, int y2) {
	int dx = x2 - x1;
	int dy = y2 - y1;
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	float x_inc = dx / (float) steps;
	float y_inc = dy / (float) steps;

	float x = x1 + 0.5;
	float y = y1 + 0.5;

	for (int i = 0; i <= steps; i++) {
    	setPixel(x, y);
    	x += x_inc;
    	y += y_inc;
	}
	glFlush();
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

void draw_segments() {
	glColor3f(1.0, 0.0, 0.0); // Red color for segments
	for (int i = 0; i < 8; i++) {
    	int x2 = xc + r * (cos(i * M_PI / 4));
    	int y2 = yc + r * (sin(i * M_PI / 4));
    	dda(xc, x2, yc, y2);
	}
}

void midpoint_circle() {
	int x = 0, y = r;
	float p = 3 - 2 * r;

	glColor3f(1.0, 1.0, 1.0); // White color for circle boundary
	plotCirclePoints(x, y);
	while (x < y) {
    	if (p < 0) {
        	p = p + 4 * x + 6;
        	x++;
    	} else {
        	p = p + 4 * (x - y) + 10;
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
	draw_segments();
	glFlush();
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);  // Black background
	glColor3f(1.0, 1.0, 1.0);      	// Default color for drawing
	glPointSize(2.0);              	// Point size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);    	// Define the 2D orthographic viewing region
}

int main(int argc, char** argv) {
	cout << "Enter the coordinates of the center of the circle (give space in between): ";
	cin >> xc >> yc;
	cout << "Enter the radius: ";
	cin >> r;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Circle with Segments");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}

