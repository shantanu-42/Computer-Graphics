#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath> // Include for sqrt and M_PI

using namespace std;

#define MAX_VERTICES 10

vector<pair<int, int>> vertices;
vector<pair<int, int>> clickedPoints;
int numVertices;

// Function to draw the polygon and arrows
void drawPolygon() {
    glColor3f(1.0f, 1.0f, 1.0f); // White color for the polygon
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numVertices; i++) {
        glVertex2i(vertices[i].first, vertices[i].second);
    }
    glEnd();

    // Draw arrows to indicate direction on edges
    glColor3f(0.0f, 0.0f, 1.0f); // Yellow color for arrows
    for (int i = 0; i < numVertices; i++) {
        int x1 = vertices[i].first;
        int y1 = vertices[i].second;
        int x2 = vertices[(i + 1) % numVertices].first;
        int y2 = vertices[(i + 1) % numVertices].second;

        // Calculate direction vector
        float dx = x2 - x1;
        float dy = y2 - y1;

        // Normalize the direction vector
        float length = sqrt(dx * dx + dy * dy);
        dx /= length;
        dy /= length;

        // Calculate arrow tip position
        float arrowTipX = x2 - 10 * dx; // 10 is the length of the arrow base
        float arrowTipY = y2 - 10 * dy;

        // Draw the arrow base
        glBegin(GL_LINES);
        glVertex2i(x2, y2);
        glVertex2f(arrowTipX, arrowTipY);
        glEnd();

        // Calculate arrowhead points
        float arrowHeadAngle = 45.0f * (M_PI / 180.0f); // Arrow head angle in radians
        float arrowHeadX1 = arrowTipX + 5 * (dx * cos(arrowHeadAngle) - dy * sin(arrowHeadAngle));
        float arrowHeadY1 = arrowTipY + 5 * (dy * cos(arrowHeadAngle) + dx * sin(arrowHeadAngle));
        float arrowHeadX2 = arrowTipX + 5 * (dx * cos(-arrowHeadAngle) - dy * sin(-arrowHeadAngle));
        float arrowHeadY2 = arrowTipY + 5 * (dy * cos(-arrowHeadAngle) + dx * sin(-arrowHeadAngle));

        // Draw the arrowhead
        glBegin(GL_LINES);
        glVertex2f(arrowTipX, arrowTipY);
        glVertex2f(arrowHeadX1, arrowHeadY1);
        glVertex2f(arrowTipX, arrowTipY);
        glVertex2f(arrowHeadX2, arrowHeadY2);
        glEnd();
    }
}

// Winding number algorithm to determine if a point is inside the polygon
int winding_number(pair<int, int> point) {
    int wn = 0; // Winding number

    const int DISTANCE = 10000; // Far distance for ray
    int x = point.first;
    int y = point.second;

    for (int i = 0; i < numVertices; i++) {
        int x1 = vertices[i].first;
        int y1 = vertices[i].second;
        int x2 = vertices[(i + 1) % numVertices].first;
        int y2 = vertices[(i + 1) % numVertices].second;

        // Check for crossings
        if (y1 <= y && y2 > y) { // Upward crossing
            if ((x2 - x1) * (y - y1) - (y2 - y1) * (x - x1) > 0) {
                wn++; // Point is to the left of the edge
            }
        } else if (y1 > y && y2 <= y) { // Downward crossing
            if ((x2 - x1) * (y - y1) - (y2 - y1) * (x - x1) < 0) {
                wn--; // Point is to the right of the edge
            }
        }
    }

    return wn; // Non-zero if inside, zero if outside
}

// Function to display the polygon and clicked points
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon(); // Draw the polygon

    // Draw clicked points
    glBegin(GL_POINTS);
    for (const auto& point : clickedPoints) {
        // Determine the color based on whether the point is inside or outside
        if (winding_number(point) != 0) {
            glColor3f(0.0f, 1.0f, 0.0f); // Green for interior points
        } else {
            glColor3f(1.0f, 0.0f, 0.0f); // Red for exterior points
        }
        glVertex2i(point.first, point.second);
    }
    glEnd();

    glFlush();
}

// Initialization function
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glPointSize(5.0f);                   // Point size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);         // Define the 2D orthographic viewing region
}

// Function to input vertices from the user
void inputVertices() {
    cout << "Enter the number of vertices for the polygon (max " << MAX_VERTICES << "): ";
    cin >> numVertices;

    while (numVertices < 3 || numVertices > MAX_VERTICES) {
        cout << "Invalid number of vertices. Please enter between 3 and " << MAX_VERTICES << ": ";
        cin >> numVertices;
    }

    vertices.resize(numVertices); // Resize the vector to hold the vertices
    for (int i = 0; i < numVertices; i++) {
        cout << "Enter the coordinates of vertex " << (i + 1) << " (space-separated): ";
        cin >> vertices[i].first >> vertices[i].second;
    }
}

// Mouse callback function
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convert mouse coordinates to OpenGL coordinates
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        y = windowHeight - y; // Invert Y coordinate

        // Store the clicked point
        clickedPoints.push_back(make_pair(x, y));

        // Check if the point is inside or outside the polygon
        if (winding_number(make_pair(x, y)) != 0) {
            cout << "Point (" << x << ", " << y << ") is inside the polygon." << endl;
        } else {
            cout << "Point (" << x << ", " << y << ") is outside the polygon." << endl;
        }

        // Redraw the scene
        glutPostRedisplay();
    }
}

// Main function
int main(int argc, char** argv) {
    inputVertices(); // Take user input for vertices

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Concave Polygon Drawing with Direction Arrows");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse); // Register mouse callback function
    glutMainLoop();

    return 0;
}
