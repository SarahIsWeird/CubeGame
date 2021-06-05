//
// Created by Sarah Klocke on 05.06.21.
//
#include "Shader.hpp"

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    int success;
    char infoLog[1024];
    std::ifstream vertexShaderFile(vertexShaderPath);
    std::stringstream vertexShaderStream;
    vertexShaderStream << vertexShaderFile.rdbuf();
    std::string vertexShaderString = vertexShaderStream.str();
    const char *vertexShaderSource = vertexShaderString.c_str();
    vertexShaderFile.close();

    unsigned char vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 1024, nullptr, infoLog);
        std::cerr << "Vertex shader " << vertexShaderPath << " compilation failed:\n"
                << infoLog << std::endl;

        glDeleteShader(vertexShader);
        return;
    }
    std::ifstream fragmentShaderFile(fragmentShaderPath);
    std::stringstream fragmentShaderStream;
    fragmentShaderStream << fragmentShaderFile.rdbuf();
    std::string fragmentShaderString = fragmentShaderStream.str();
    const char *fragmentShaderSource = fragmentShaderString.c_str();
    fragmentShaderFile.close();

    unsigned char fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 1024, nullptr, infoLog);
        std::cerr << "Fragment shader " << fragmentShaderPath << " compilation failed:\n"
                << infoLog << std::endl;

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    this->id = glCreateProgram();
    glAttachShader(this->id, vertexShader);
    glAttachShader(this->id, fragmentShader);
    glLinkProgram(this->id);
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if (!success) {
        glGetProgramInfoLog(this->id, 1024, nullptr, infoLog);
        std::cerr << "Error linking the shader program:\n"
                  << infoLog << std::endl;

        return;
    }

    this->projectionLoc = glGetUniformLocation(this->id, "projection");
    this->viewLoc = glGetUniformLocation(this->id, "view");
    this->modelLoc = glGetUniformLocation(this->id, "model");
}

void Shader::use() const {
    glUseProgram(this->id);
}

void Shader::SetProjectionMatrix(glm::mat4 matrix) const {
    glUniformMatrix4fv(this->projectionLoc, 1, false, glm::value_ptr(matrix));
}

void Shader::SetViewMatrix(glm::mat4 matrix) const {
    glUniformMatrix4fv(this->viewLoc, 1, false, glm::value_ptr(matrix));
}

void Shader::SetModelMatrix(glm::mat4 matrix) const {
    glUniformMatrix4fv(this->modelLoc, 1, false, glm::value_ptr(matrix));
}
