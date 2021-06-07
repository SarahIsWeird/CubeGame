//
// Created by Sarah Klocke on 05.06.21.
//

#include "Cube.hpp"

#include "../models/cube.hpp"

Cube::Cube(unsigned int id) : id(id), modelMatrix(1.0f) {

}

void Cube::Render() {
    glBindVertexArray(id);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / 5);
}

glm::mat4 &Cube::GetModelMatrix() {
    return this->modelMatrix;
}