#include <GL/glut.h>

void drawCharacter() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(-0.5f, 0.0f, 0.0f);
    glScalef(0.1f, 0.1f, 0.1f);

    glBegin(GL_LINES);
    // Left vertical line of 'N'
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-1.0f, 1.0f);

    // Diagonal of 'N'
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);

    // Right vertical line of 'N'
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glEnd();

    glPopMatrix();

    glFlush();
}

void initOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.5, 1.5, -1.5, 1.5);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Character N using Stroke Method");

    initOpenGL();
    glutDisplayFunc(drawCharacter);
    glutMainLoop();

    return 0;
}

