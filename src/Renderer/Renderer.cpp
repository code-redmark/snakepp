#include "Renderer.hpp"
#include "../utils.hpp"

void Renderer::initialize(const uint32_t width, const uint32_t height) {
    windowSize = glm::vec2(static_cast<float>(width), static_cast<float>(height));
    
    try {
        initializeWindow();
        setupOpenGL();
    } catch (const std::exception& e) {
        SPP_LOG_ERROR("Renderer initialization failed: " << e.what());
        throw;
    }
}

bool Renderer::render() {
    glfwPollEvents();
 
    glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    glClear(GL_COLOR_BUFFER_BIT);

    drawRectangle(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(1.f, 0.f, 0.f, 1.0f));
    drawRectangle(glm::vec2(0.1f, -0.1f), glm::vec2(1.0f, 1.0f), glm::vec4(0.f, 0.f, 1.f, 1.0f));
    
    glfwSwapBuffers(window);

    return !glfwWindowShouldClose(window);
}

void Renderer::drawRectangle(glm::vec2 position, glm::vec2 size, glm::vec4 color) {    
    glUseProgram(shaderProgram);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));
    
    GLint modelLoc = glGetUniformLocation(shaderProgram, "uModel");
    if (modelLoc == -1) {
        SPP_THROW_ERROR("Failed to get uniform location for 'uModel'");
    }
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

    GLint colorLoc = glGetUniformLocation(shaderProgram, "uColor");
    if (colorLoc == -1) {
        SPP_THROW_ERROR("Failed to get uniform location for 'uColor'");
    }
    glUniform4fv(colorLoc, 1, &color[0]);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer::initializeWindow() {
    
    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "[GLFW ERROR " << error << "] "
                  << description << '\n';
    });
   
    auto init = glfwInit();
    if (!init) {
        SPP_THROW_ERROR("Failed to initialize GLFW");
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowSize.x, windowSize.y, "Snake++", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        SPP_THROW_ERROR("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        SPP_THROW_ERROR("Failed to initialize GLAD");
    }
    glfwSwapInterval(1);
}

void Renderer::setupOpenGL() {
    
    try {
        createGeometry();
        createShaderProgram(vertexShaderSource, fragmentShaderSource);
    } catch (const std::exception& e) {
        SPP_LOG_ERROR("OpenGL setup failed: " << e.what());
        throw;
    }

    SPP_LOG_DEBUG("OpenGL setup completed successfully");
}

void Renderer::createGeometry() {
    glCreateBuffers(1, &VBO);
    if (!VBO) {
        SPP_THROW_ERROR("Failed to create VBO");
    } else glNamedBufferData(VBO, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);
    
    glCreateBuffers(1, &EBO);
    if (!EBO) {
        SPP_THROW_ERROR("Failed to create EBO");
    } else glNamedBufferData(EBO, sizeof(rectIndices), rectIndices, GL_STATIC_DRAW);


    glCreateVertexArrays(1, &VAO);
    if (!VAO) {
        SPP_THROW_ERROR("Failed to create VAO");
    }
    
    glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 2 * sizeof(float));
    glVertexArrayElementBuffer(VAO, EBO);

    glEnableVertexArrayAttrib(VAO, 0);

    glVertexArrayAttribFormat(VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(VAO, 0, 0);
    
    
    SPP_LOG_DEBUG("Geometry created successfully: VAO=" << VAO << ", VBO=" << VBO << ", EBO=" << EBO);

    glBindVertexArray(VAO);
}

void Renderer::createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        SPP_THROW_ERROR("Vertex shader compilation failed: " + infoLog);
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        SPP_THROW_ERROR("Fragment shader compilation failed: " + infoLog);
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        SPP_THROW_ERROR("Shader program linking failed: " + infoLog);
    }

    SPP_LOG_DEBUG("Shader program created successfully with ID: " << shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

