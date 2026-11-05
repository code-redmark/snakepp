#include "Renderer.hpp"

void Renderer::initialize() {
    initializeWindow();
}

bool Renderer::render() {
    glfwPollEvents();

    glad_glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    glad_glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);

    return !glfwWindowShouldClose(window);
}

void Renderer::initializeWindow() {
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "Snake++", nullptr, nullptr);
    
    if (!window) {
        LOG_ERROR("Failed to create GLFW window");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL((GLADloadfunc)glfwGetProcAddress);
    glfwSwapInterval(1);
}