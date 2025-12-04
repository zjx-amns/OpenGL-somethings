#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

std::string loadShaderSourceFromFile(const std::string& filename);
GLuint compileShader(GLenum type, const std::string& source);
GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader);
GLuint createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
