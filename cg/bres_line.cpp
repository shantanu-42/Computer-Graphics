#include <GL/glut.h>
#include <cmath>

void plotPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawLineBresenham(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int abs_dx = abs(dx);
    int abs_dy = abs(dy);
    int sx = (dx >= 0) ? 1 : -1; // Step in x
    int sy = (dy >= 0) ? 1 : -1; // Step in y

    // Error term
    int err = abs_dx - abs_dy;

    while (true) {
        plotPixel(x1, y1); // Plot the pixel at (x1, y1)

        // Check if we reached the end point
        if (x1 == x2 && y1 == y2) break;

        int err2 = err * 2; // Double the error term
        if (err2 > -abs_dy) {
            err -= abs_dy;
            x1 += sx; // Move in x direction
        }
        if (err2 < abs_dx) {
            err += abs_dx;
            y1 += sy; // Move in y direction
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Set color to red

    // Draw a line from (10, 20) to (80, 70)
    drawLineBresenham(10, 20, 80, 70);

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(1.0, 0.0, 0.0); // Red color for the line
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 100, 0, 100); // Set coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham's Line Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

