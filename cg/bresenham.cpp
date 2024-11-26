#include <GL/glut.h>
#include <cmath>

// Circle parameters
int centerX = 400;
int centerY = 300;
int radius = 100;

// Bresenham's Circle Drawing Algorithm
void drawCircle(int cx, int cy, int r) {
    int x = 0;
    int y = r;
    int p = 3 - 2 * r; // Initial decision parameter

    // Draw initial points
    glBegin(GL_POINTS);
    glVertex2i(cx + x, cy + y);
    glVertex2i(cx - x, cy + y);
    glVertex2i(cx + x, cy - y);
    glVertex2i(cx - x, cy - y);
    glVertex2i(cx + y, cy + x);
    glVertex2i(cx - y, cy + x);
    glVertex2i(cx + y, cy - x);
    glVertex2i(cx - y, cy - x);
    glEnd();

    while (x < y) {
        x++;
        if (p < 0) {
            p += 4 * x + 6;
        } else {
            y--;
            p += 4 * (x - y) + 10;
        }

        // Draw points
        glBegin(GL_POINTS);
        glVertex2i(cx + x, cy + y);
        glVertex2i(cx - x, cy + y);
        glVertex2i(cx + x, cy - y);
        glVertex2i(cx - x, cy - y);
        glVertex2i(cx + y, cy + x);
        glVertex2i(cx - y, cy + x);
        glVertex2i(cx + y, cy - x);
        glVertex2i(cx - y, cy - x);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the circle
    drawCircle(centerX, centerY, radius);

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set the background color to black
    glColor3f(1.0, 1.0, 1.0);         // Set the drawing color to white
    glPointSize(1.0);                  // Set the point size
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 800.0, 0.0, 600.0); // Set the coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham's Circle Algorithm");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

