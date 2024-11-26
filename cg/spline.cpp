#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    float x, y;
    Point() : x(0), y(0) {}
    Point(float _x, float _y) : x(_x), y(_y) {}
};

Point cubicHermite(float t, const Point& p0, const Point& p1, const Point& m0, const Point& m1) {
    float h00 = (2 * t * t * t) - (3 * t * t) + 1;
    float h10 = (t * t * t) - (2 * t * t) + t;
    float h01 = (-2 * t * t * t) + (3 * t * t);
    float h11 = (t * t * t) - (t * t);
    float x = h00 * p0.x + h10 * m0.x + h01 * p1.x + h11 * m1.x;
    float y = h00 * p0.y + h10 * m0.y + h01 * p1.y + h11 * m1.y;
    return Point(x, y);
}

std::vector<Point> controlPoints;
std::vector<Point> tangents;
int subdivisions = 100;

void calculateTangents() {
    tangents.clear();
    for (size_t i = 0; i < controlPoints.size(); ++i) {
        if (i == 0) {
            tangents.push_back(Point(
                (controlPoints[i + 1].x - controlPoints[i].x) / 2,
                (controlPoints[i + 1].y - controlPoints[i].y) / 2
            ));
        } else if (i == controlPoints.size() - 1) {
            tangents.push_back(Point(
                (controlPoints[i].x - controlPoints[i - 1].x) / 2,
                (controlPoints[i].y - controlPoints[i - 1].y) / 2
            ));
        } else {
            tangents.push_back(Point(
                (controlPoints[i + 1].x - controlPoints[i - 1].x) / 2,
                (controlPoints[i + 1].y - controlPoints[i - 1].y) / 2
            ));
        }
    }
}

void renderSpline() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Draw control points
    glColor3f(0.0f, 0.0f, 1.0f);  // Blue for control points
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (const auto& p : controlPoints) {
        glVertex2f(p.x, p.y);
    }
    glEnd();

    // Draw Hermite spline
    glColor3f(1.0f, 0.0f, 0.0f);  // Red for the spline
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    for (size_t i = 1; i < controlPoints.size(); ++i) {
        for (int j = 0; j <= subdivisions; ++j) {
            float t = j / float(subdivisions);
            Point p = cubicHermite(t, controlPoints[i - 1], controlPoints[i], tangents[i - 1], tangents[i]);
            glVertex2f(p.x, p.y);
        }
    }
    glEnd();

    glutSwapBuffers();
}

void initOpenGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // White background
    glEnable(GL_DEPTH_TEST);
    glPointSize(5.0f);
    glLineWidth(2.0f);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);  // Adjust the orthographic view to the window size
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    int numControlPoints;
    std::cout << "Enter the number of control points: ";
    std::cin >> numControlPoints;
    controlPoints.resize(numControlPoints);

    for (int i = 0; i < numControlPoints; ++i) {
        std::cout << "Control point " << i + 1 << " (x y): ";
        std::cin >> controlPoints[i].x >> controlPoints[i].y;
    }

    calculateTangents();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cubic Hermite Spline");
    initOpenGL();
    glutDisplayFunc(renderSpline);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}

