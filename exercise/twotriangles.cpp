#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <fstream>
#include "util.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

int main(int, char**)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    auto window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Max Number of vetex attribs: " << nrAttributes << std::endl;
    auto shaderProgram = load_program("../shaders/vertex_uniform.glsl", "../shaders/fragment_uniform.glsl");

    /* -------------------------------------------------------------------------- */
    /*     set up vertex data (and buffer(s)) and configure vertex attributes     */
    /* -------------------------------------------------------------------------- */
    float vertices0[] = {
        -1.0f, -0.5f, 0.0f, // left
        0.0f, -0.5f, 0.0f, // right
        -0.5f, 0.5f, 0.0f // top
    };
    float vertices1[] = {
        0.0f, -0.5f, 0.0f, // left
        1.0f, -0.5f, 0.0f, // right
        0.5f, 0.5f, 0.0f // top
    };
    float color0[] = { 0.5f, 0.5f, 0.5f };
    float color1[] = { 0.5f, 0.8f, 0.2f };
    GLuint VAO[2], VBO[2];
    // unsigned int VBO0, VAO0, VBO1, VBO1;
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices0), vertices0, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // glBindVertexArray(0);
    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* -------------------------------------------------------------------------- */
    /*                           main  render loop                                */
    /* -------------------------------------------------------------------------- */
    while (!glfwWindowShouldClose(window)) {
        // input

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[0]); // seeing as we only have a single VAO there's no need to bind it every time, but
                                   // we'll do so to keep things a bit more organized
        int colorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform3f(colorLocation, color0[0], color0[1], color0[2]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0);
        glBindVertexArray(VAO[1]);
        colorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform3f(colorLocation, color1[0], color1[1], color1[2]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
        // check and call events and swap the buffer
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
