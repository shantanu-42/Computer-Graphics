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
    int d = 3 - 2 * r;

    while (x <= y) {
        plotPixel(h + x, k + y);
        plotPixel(h - x, k + y);
        plotPixel(h + x, k - y);
        plotPixel(h - x, k - y);
        plotPixel(h + y, k + x);
        plotPixel(h - y, k + x);
        plotPixel(h + y, k - x);
        plotPixel(h - y, k - x);

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void drawDivisions(int h, int k, int r) {
    for (int i = 0; i < 8; ++i) {
        float angle = (M_PI / 4) * i; // 45 degrees in radians
        int x = static_cast<int>(r * cos(angle));
        int y = static_cast<int>(r * sin(angle));
        glBegin(GL_LINES);
        glVertex2i(h, k);  // Center of the circle
        glVertex2i(h + x, k + y); // Point on the circle
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Red color for the circle
    drawCircle(0, 0, 50); // Draw a circle centered at (0, 0) with radius 50

    glColor3f(0.0, 0.0, 1.0); // Blue color for divisions
    drawDivisions(0, 0, 50); // Draw lines dividing the circle

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(1.0, 0.0, 0.0); // Initial color for the circle
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Circle with Divisions");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

