//
// Created by Sarah Klocke on 05.06.21.
//

#ifndef CUBE_GAME_CUBE_HPP
#define CUBE_GAME_CUBE_HPP

#include <glad/glad.h>

#include "Object.hpp"

class Cube : Object {
public:
    explicit Cube(unsigned int id);

    glm::mat4 &GetModelMatrix() override;
    void Render() override;

private:
    unsigned int id;

    glm::mat4 modelMatrix;
};


#endif //CUBE_GAME_CUBE_HPP
