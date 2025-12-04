#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include "shader.hpp"

int main() {
    if (!glfwInit()) { // 初始化 GLFW
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 设置 GLFW 版本为 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 使用核心 OpenGL 版本

    GLFWwindow * window = glfwCreateWindow(800, 600, "OpenGL Test", nullptr, nullptr); // 创建 GLFW 窗口
    
    if (!window) { // 检查 GLFW 窗口是否创建成功
        std::cout << "ERROR : Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << "Window created successfully" << std::endl;

    glfwMakeContextCurrent(window); // 设置 GLFW 窗口为当前上下文
    glfwSetWindowPos(window, -1000, 100); // 设置 GLFW 窗口位置
    
    if (glewInit() != GLEW_OK)
    {
        std::cout << "ERROR : Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::string vertexShaderSource = loadShaderSourceFromFile("triangle.vert");
    std::string fragmentShaderSource = loadShaderSourceFromFile("triangle.frag");
    GLuint program = createShaderProgram(vertexShaderSource, fragmentShaderSource); // 创建着色器程序

    std::vector<float> vertices = 
    {
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    }; // 顶点数据: 三角形

    GLuint VBO; // 顶点缓冲区对象
    glGenBuffers(1, &VBO); // 创建缓冲区对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // 绑定缓冲区对象，表明这个缓冲区用于存储顶点数据
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW); // 加载顶点数据到缓冲区对象，参数：目标缓冲区类型，数据大小，数据指针，数据用法（使用模式）-> 表明数据将会一次性上传，永久驻留在显存中
    glBindBuffer(GL_ARRAY_BUFFER, 0); // 解绑缓冲区对象

    GLuint VAO; // 顶点数组对象
    glGenVertexArrays(1, &VAO); // 创建顶点数组对象
    glBindVertexArray(VAO); // 绑定顶点数组对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // 绑定缓冲区对象
    
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0); // 配置顶点属性，参数：属性索引，分量数量，数据类型，是否归一化，步长，偏移量
    glEnableVertexAttribArray(0); // 启用顶点属性

    glBindBuffer(GL_ARRAY_BUFFER, 0); // 解绑缓冲区对象
    glBindVertexArray(0); // 解绑顶点数组对象(VAO)

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 设置背景颜色为蓝色
        glClear(GL_COLOR_BUFFER_BIT); // 清除颜色缓冲区

        glUseProgram(program); // 使用程序
        glBindVertexArray(VAO); // 绑定顶点数组对象
        glDrawArrays(GL_TRIANGLES, 0, 3); // 绘制三角形，参数：绘制模式，起始顶点索引（因为是从顶点开始，所以为0），顶点数量（三角形三个顶点）

        glfwSwapBuffers(window); // 交换缓冲区
        // 窗口渲染代码
        glfwPollEvents();
    }

    glfwTerminate(); // 终止 GLFW

    return 0;
}