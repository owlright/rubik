#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// 图片路径
const char* imagePath = "../images/lenna.png";

// 顶点着色器源码
const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec2 aTexCoord;\n"
                                 "out vec2 TexCoord;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos, 1.0);\n"
                                 "   TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
                                 "}\0";

// 片段着色器源码
const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec2 TexCoord;\n"
                                   "uniform sampler2D texture1;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = texture(texture1, TexCoord);\n"
                                   "}\n\0";

// 顶点数据
float vertices[] = {
    // 位置          // 纹理坐标
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // 右上角
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // 右下角
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // 左下角
    -1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // 左上角
};

unsigned int indices[] = {
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};

GLuint createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    // 创建顶点着色器
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // 创建片段着色器
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // 创建着色器程序
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // 删除着色器，它们已经链接到我们的程序中了
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main(void)
{
    // 初始化GLFW
    glfwInit();

    // 获取图片信息
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* imageData = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (imageData == NULL) {
        printf("Failed to load image.\n");
        return -1;
    } else {
        printf("w: %d, h: %d, channels: %d\n", width, height, nrChannels);
    }
    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(width, height, "Texture", NULL, NULL);

    // 获取OpenGL上下文
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    // 生成纹理ID
    GLuint textureID;
    glGenTextures(1, &textureID);

    // 绑定纹理
    glBindTexture(GL_TEXTURE_2D, textureID);
    // 设置纹理环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // 设置缩小和放大过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 将图片数据上传到纹理
    if (nrChannels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    } else if (nrChannels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    }
    // 生成mipmap
    glGenerateMipmap(GL_TEXTURE_2D);
    // 释放图片数据
    stbi_image_free(imageData);

    // 在这里创建VAO，VBO和EBO
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 在这里设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 在这里创建着色器程序
    GLuint shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

    while (!glfwWindowShouldClose(window)) {

        // 清除颜色缓冲
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        // 绑定纹理
        glBindTexture(GL_TEXTURE_2D, textureID);

        // 在这里绘制纹理quad
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 释放资源
    glDeleteTextures(1, &textureID);
    glfwTerminate();

    return 0;
}