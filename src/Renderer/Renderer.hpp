#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

constexpr float rectVertices[] = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.5f,  0.5f,
    -0.5f,  0.5f
};

constexpr unsigned int rectIndices[] = {
    0, 1, 2,
    2, 3, 0
};

constexpr const char* vertexShaderSource = R"(
#version 460 core
layout (location = 0) in vec2 aPos;

uniform mat4 uModel;
uniform vec4 uColor;

out vec4 vertexColor;

void main() {
    gl_Position = uModel * vec4(aPos, 0.0, 1.0);
    vertexColor = uColor;
}

)";

constexpr const char* fragmentShaderSource = R"(
#version 460 core
in vec4 vertexColor;
out vec4 FragColor;

void main() {
    FragColor = vertexColor;
}

)";


class Renderer {

private:
    GLFWwindow *window;
    glm::vec2 windowSize;

    glm::vec4 bgColor = glm::vec4(0.0f, 0.5f, 0.0f, 1.0f);

    GLuint VAO, VBO, EBO;
    GLuint shaderProgram;
    
    void drawRectangle(glm::vec2 position, glm::vec2 size, glm::vec4 color);

    void initializeWindow();
    void setupOpenGL();
    
    // Creates a VAO, VBO, and EBO for a rectangle and sets up the vertex attributes
    void createGeometry();
    void createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

public:
    bool render();

    void initialize(uint32_t width, uint32_t height);
};