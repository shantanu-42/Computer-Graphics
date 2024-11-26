#include <GL/glut.h>
#include <cmath>

void plotPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawCircle(int h, int k, int r) {
    int x = 0;
    int y = r;
    int d = 1 - r; // Decision parameter

    // Draw the initial points in all octants
    plotPixel(h + x, k + y);
    plotPixel(h - x, k + y);
    plotPixel(h + x, k - y);
    plotPixel(h - x, k - y);
    plotPixel(h + y, k + x);
    plotPixel(h - y, k + x);
    plotPixel(h + y, k - x);
    plotPixel(h - y, k - x);

    while (x < y) {
        x++;

        if (d < 0) {
            d = d + 2 * x + 1; // Move to the next point
        } else {
            y--;
            d = d + 2 * x - 2 * y + 1; // Move to the next point and reduce y
        }

        // Plot the points in all octants
        plotPixel(h + x, k + y);
        plotPixel(h - x, k + y);
        plotPixel(h + x, k - y);
        plotPixel(h - x, k - y);
        plotPixel(h + y, k + x);
        plotPixel(h - y, k + x);
        plotPixel(h + y, k - x);
        plotPixel(h - y, k - x);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Red color for the circle
    drawCircle(0, 0, 50); // Draw a circle centered at (0, 0) with radius 50

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(1.0, 0.0, 0.0); // Red color for the circle
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Circle Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

