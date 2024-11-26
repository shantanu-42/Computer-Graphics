#include <GL/glut.h>
#include <cmath>

void plotPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawEllipse(int h, int k, int a, int b) {
    float x, y;
    float p1, p2;

    // Region 1
    p1 = b * b - (a * a * b) + (0.25 * a * a);
    x = 0;
    y = b;

    while ((2 * b * b * x) < (2 * a * a * y)) {
        plotPixel(h + x, k + y);
        plotPixel(h - x, k + y);
        plotPixel(h + x, k - y);
        plotPixel(h - x, k - y);
        x++;

        if (p1 < 0) {
            p1 += (2 * b * b * x) + (b * b);
        } else {
            y--;
            p1 += (2 * b * b * x) - (2 * a * a * y) + (b * b);
        }
    }

    // Region 2
    p2 = (b * b * (x + 0.5) * (x + 0.5)) + (a * a * (y - 1) * (y - 1)) - (a * a * b * b);
    while (y > 0) {
        plotPixel(h + x, k + y);
        plotPixel(h - x, k + y);
        plotPixel(h + x, k - y);
        plotPixel(h - x, k - y);
        y--;

        if (p2 > 0) {
            p2 += (a * a) - (2 * a * a * y);
        } else {
            x++;
            p2 += (2 * b * b * x) - (2 * a * a * y) + (a * a);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Set the color to red

    // Draw an ellipse centered at (0, 0) with radii a=50, b=30
    drawEllipse(0, 0, 50, 30);

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(1.0, 0.0, 0.0); // Red color for the ellipse
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Ellipse Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

