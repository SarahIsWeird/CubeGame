//
// Created by Sarah Klocke on 05.06.21.
//

#ifndef CUBE_GAME_SHADER_HPP
#define CUBE_GAME_SHADER_HPP

#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    void use() const;

    void SetProjectionMatrix(glm::mat4 matrix) const;
    void SetViewMatrix(glm::mat4 matrix) const;
    void SetModelMatrix(glm::mat4 matrix) const;

private:
    unsigned int id;

    int projectionLoc;
    int viewLoc;
    int modelLoc;
};

#endif //CUBE_GAME_SHADER_HPP
