#include <GL/glut.h>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_VERTICES 10

vector<pair<int, int>> vertices;
vector<pair<int, int>> clickedPoints;
int numVertices;

// Function to draw the polygon
void drawPolygon() {
    glColor3f(1.0, 1.0, 1.0); // White color for the polygon
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numVertices; i++) {
        glVertex2i(vertices[i].first, vertices[i].second);
    }
    glEnd();
}

// Ray-casting algorithm to determine if a point is inside the polygon
bool ray_casting(pair<int, int> point) {
    int x = point.first, y = point.second;
    int num_vertices = vertices.size();
    int crossings = 0;

    for (int i = 0; i < num_vertices; i++) {
        int x1 = vertices[i].first;
        int y1 = vertices[i].second;
        int x2 = vertices[(i + 1) % num_vertices].first;
        int y2 = vertices[(i + 1) % num_vertices].second;

        // Check if the edge intersects with the ray extending to the right
        if ((y1 > y) != (y2 > y)) { // Only consider edges that straddle the horizontal line
            // Compute the x-coordinate of the intersection of the edge with the horizontal line
            float intersectionX = (float)(x2 - x1) * (y - y1) / (y2 - y1) + x1;
            if (x < intersectionX) {
                crossings++; // Count the intersection
            }
        }
    }
    return crossings % 2 == 1; // Inside if odd number of crossings
}

// Function to display the polygon and clicked points
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon(); // Draw the polygon

    // Draw clicked points
    glBegin(GL_POINTS);
    for (const auto& point : clickedPoints) {
        // Determine the color based on whether the point is inside or outside
        if (ray_casting(point)) {
            glColor3f(0.0, 1.0, 0.0); // Green for interior points
        } else {
            glColor3f(1.0, 0.0, 0.0); // Red for exterior points
        }
        glVertex2i(point.first, point.second);
    }
    glEnd();

    glFlush();
}

// Initialization function
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glPointSize(5.0);                 // Point size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);       // Define the 2D orthographic viewing region
}

// Function to input vertices from the user
void inputVertices() {
    printf("Enter the number of vertices for the polygon (max %d): ", MAX_VERTICES);
    scanf("%d", &numVertices);

    while (numVertices < 3 || numVertices > MAX_VERTICES) {
        printf("Invalid number of vertices. Please enter between 3 and %d: ", MAX_VERTICES);
        scanf("%d", &numVertices);
    }

    vertices.resize(numVertices); // Resize the vector to hold the vertices
    for (int i = 0; i < numVertices; i++) {
        printf("Enter the coordinates of vertex %d (give space in between): ", i + 1);
        scanf("%d%d", &vertices[i].first, &vertices[i].second);
    }
}

// Mouse callback function
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convert mouse coordinates to OpenGL coordinates
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        y = windowHeight - y; // Invert Y coordinate

        // Store the clicked point
        clickedPoints.push_back(make_
pair(x, y));

        // Check if the point is inside or outside the polygon
        if (ray_casting(make_pair(x, y))) {
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
    glutCreateWindow("Concave Polygon Drawing");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse); // Register mouse callback function
    glutMainLoop();

    return 0;
}

