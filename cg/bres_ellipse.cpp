#include <GL/glut.h>
#include <cmath>

void plotPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawEllipse(int h, int k, int a, int b) {
    int x = 0;
    int y = b;
    int a2 = a * a;
    int b2 = b * b;
    int d1 = b2 - (a2 * b) + (0.25 * a2);
    
    // First region
    while ((2 * b2 * x) < (2 * a2 * y)) {
        plotPixel(h + x, k + y);
        plotPixel(h - x, k + y);
        plotPixel(h + x, k - y);
        plotPixel(h - x, k - y);
        x++;

        if (d1 < 0) {
            d1 += (2 * b2 * x) + b2;
        } else {
            y--;
            d1 += (2 * b2 * x) - (2 * a2 * y) + b2;
        }
    }

    // Second region
    int d2 = (b2 * (x + 0.5) * (x + 0.5)) + (a2 * (y - 1) * (y - 1)) - (a2 * b2);
    while (y > 0) {
        plotPixel(h + x, k + y);
        plotPixel(h - x, k + y);
        plotPixel(h + x, k - y);
        plotPixel(h - x, k - y);
        y--;

        if (d2 > 0) {
            d2 += a2 - (2 * a2 * y);
        } else {
            x++;
            d2 += (2 * b2 * x) - (2 * a2 * y) + a2;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(2.0, 0.0, 1.0);
    drawEllipse(0, 0, 50, 30); 
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(2.0, 0.0, 1.0); // Red color for the ellipse
    glPointSize(3.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham's Ellipse Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

