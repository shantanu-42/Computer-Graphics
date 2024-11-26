#include <GL/glut.h>
#include<bits/stdc++.h>
using namespace std;

#define MAX_VERTICES 10

int vertices[MAX_VERTICES][2];
int numVertices;


// Function to calculate the cross product of two vectors
int crossProduct(int x1, int y1, int x2, int y2) {
    return x1 * y2 - y1 * x2;
}

// Function to check if the polygon is concave
bool isConcave() {
    int sign = 0;

    for (int i = 0; i < numVertices; i++) {
        int x1 = vertices[i][0];
        int y1 = vertices[i][1];
        int x2 = vertices[(i + 1) % numVertices][0];
        int y2 = vertices[(i + 1) % numVertices][1];
        int x3 = vertices[(i + 2) % numVertices][0];
        int y3 = vertices[(i + 2) % numVertices][1];

        int cp = crossProduct(x2 - x1, y2 - y1, x3 - x2, y3 - y2);

        if (cp < 0) {
            if (sign == 0) {
                sign = -1;
            }
            else if (sign == 1) {
                return true; // Convex
            }
        }
        else if (cp > 0) {
            if (sign == 0) {
                sign = 1;
            }
            else if (sign == -1) {
                return true; // Convex
            }
        }
    }

    return false; // Concave
}

void drawPolygon() {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numVertices; i++) {
        glVertex2i(vertices[i][0], vertices[i][1]);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon(); // Call the polygon drawing function
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glColor3f(1.0, 1.0, 1.0);         // White drawing color
    glPointSize(2.0);                 // Point size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);       // Define the 2D orthographic viewing region
}

void inputVertices() {
    printf("Enter the number of vertices for the polygon (max %d): ", MAX_VERTICES);
    scanf("%d", &numVertices);

    while (numVertices < 3 || numVertices > MAX_VERTICES) {
        printf("Invalid number of vertices. Please enter between 3 and %d: ", MAX_VERTICES);
        scanf("%d", &numVertices);
    }

    for (int i = 0; i < numVertices; i++) {
        printf("Enter the coordinates of vertex %d (give space in between): ", i + 1);
        scanf("%d%d", &vertices[i][0], &vertices[i][1]);
    }
}

int main(int argc, char** argv) {
    while (true) {
        inputVertices(); // Take user input for vertices

        if (isConcave()) {
            break; // Exit the loop if the polygon is concave
        } else {
            printf("These coordinates will form a convex polygon. Please reenter the coordinates.\n");
        }
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Concave Polygon Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

