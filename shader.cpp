#include "shader.hpp"

std::string loadShaderSourceFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return source;
}

GLuint compileShader(GLenum type, const std::string& source)
{
    GLuint shader = glCreateShader(type); // 创建着色器
    const char* sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, nullptr); // 加载着色器源代码，参数：着色器ID，源码数量，源码字符串，源码长度
    glCompileShader(shader); // 编译着色器
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success); // 检查编译是否成功

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR : SHADER_COMPILATION_ERROR: Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader: " << infoLog << std::endl;
        return 0;
    }

    return shader;
}

GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint program = glCreateProgram(); // 创建程序
    glAttachShader(program, vertexShader); // 附加顶点着色器到程序
    glAttachShader(program, fragmentShader); // 附加片段着色器到程序
    glLinkProgram(program); // 链接程序

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success); // 检查链接是否成功

    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "ERROR : PROGRAM_LINKING_ERROR: Failed to link program: " << infoLog << std::endl;
        return 0;
    }

    return program;
}



GLuint createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource); // 编译顶点着色器
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource); // 编译片段着色器
    GLuint program = linkProgram(vertexShader, fragmentShader); // 链接程序
    glDeleteShader(vertexShader); // 删除顶点着色器
    glDeleteShader(fragmentShader); // 删除片段着色器
    return program;
}
