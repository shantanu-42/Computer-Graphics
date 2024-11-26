#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <iostream>

const GLuint WIDTH = 800, HEIGHT = 600;

// Function to plot a point in the buffer
void plotPixel(std::vector<GLfloat>& vertices, float x, float y) {
    vertices.push_back(x);
    vertices.push_back(y);
}

// Midpoint Ellipse Algorithm to create and return a VBO containing ellipse vertices
GLuint createEllipseVBO(int a, int b, int num_segments) {
    std::vector<GLfloat> vertices;
    
    int x = 0;
    int y = b;
    
    // Initial decision parameter for ellipse
    int p1 = b * b - a * a * b + 0.25 * a * a;
    
    // Region 1
    while (2 * b * b * x <= 2 * a * a * y) {
        plotPixel(vertices, x / (float)a, y / (float)b);
        plotPixel(vertices, -x / (float)a, y / (float)b);
        plotPixel(vertices, x / (float)a, -y / (float)b);
        plotPixel(vertices, -x / (float)a, -y / (float)b);

        if (p1 < 0) {
            x++;
            p1 += 2 * b * b * x + b * b;
        } else {
            x++;
            y--;
            p1 += 2 * b * b * x - 2 * a * a * y + b * b;
        }
    }
    
    // Decision parameter for Region 2
    int p2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
    
    // Region 2
    while (y >= 0) {
        plotPixel(vertices, x / (float)a, y / (float)b);
        plotPixel(vertices, -x / (float)a, y / (float)b);
        plotPixel(vertices, x / (float)a, -y / (float)b);
        plotPixel(vertices, -x / (float)a, -y / (float)b);

        if (p2 > 0) {
            y--;
            p2 -= 2 * a * a * y + a * a;
        } else {
            x++;
            y--;
            p2 += 2 * b * b * x - 2 * a * a * y + a * a;
        }
    }
    
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    
    return VBO;
}

// Function to create a VAO and link it with the VBO
GLuint createEllipseVAO(GLuint VBO) {
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    
    return VAO;
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Ellipse", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    
    GLuint ellipseVBO = createEllipseVBO(200, 100, 360); // Semi-major axis 200, semi-minor axis 100
    GLuint ellipseVAO = createEllipseVAO(ellipseVBO);
    
    // Set up viewport and orthographic projection
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBindVertexArray(ellipseVAO);
        glDrawArrays(GL_LINE_LOOP, 0, 360);  // Adjust based on the number of vertices
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &ellipseVAO);
    glDeleteBuffers(1, &ellipseVBO);
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}

