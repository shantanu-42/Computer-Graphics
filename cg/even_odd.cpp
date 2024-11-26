#include <iostream>
#include <GL/glut.h>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

vector<Point> points;      // Polygon vertices
vector<Point> testPoints;  // Test points

// Function to check if a point is inside the polygon using the odd-even rule
bool isInside(Point p) {
    int count = 0;
    size_t n = points.size();
    for (size_t i = 0; i < n; i++) {
        Point p1 = points[i];
        Point p2 = points[(i + 1) % n];

        if (p.y > min(p1.y, p2.y) && p.y <= max(p1.y, p2.y) && p1.y != p2.y) {
            float xinters = (float)(p.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;
            if (p.x < xinters) {
                count++;
            }
        }
    }
    return (count % 2) == 1;
}

// OpenGL initialization
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    glPointSize(5.0f);
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw polygon
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    for (const Point& p : points) {
        glVertex2i(p.x, p.y);
    }
    glEnd();

    // Draw test points
    glBegin(GL_POINTS);
    for (const Point& p : testPoints) {
        if (isInside(p)) {
            glColor3f(0.0f, 1.0f, 0.0f);  // Green for inside
        } else {
            glColor3f(1.0f, 0.0f, 0.0f);  // Red for outside
        }
        glVertex2i(p.x, p.y);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    int vertexCount, testPointCount;

    // Input polygon vertices
    cout << "Enter the number of vertices: ";
    cin >> vertexCount;
    if (vertexCount < 3) {
        cout << "A polygon must have at least 3 vertices." << endl;
        return 1;
    }
    points.resize(vertexCount);
    for (int i = 0; i < vertexCount; i++) {
        cout << "Enter coordinates for vertex " << i + 1 << " (x y): ";
        cin >> points[i].x >> points[i].y;
    }

    // Input test points
    cout << "Enter the number of test points: ";
    cin >> testPointCount;
    testPoints.resize(testPointCount);
    for (int i = 0; i < testPointCount; i++) {
        cout << "Enter coordinates for test point " << i + 1 << " (x y): ";
        cin >> testPoints[i].x >> testPoints[i].y;
    }

    // Initialize OpenGL and create window
    glutInit(&argc, argv);
    glutInitWindowPosition(400, 400);
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Polygon with Odd-Even Rule");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

