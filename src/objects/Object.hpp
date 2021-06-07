//
// Created by Sarah Klocke on 05.06.21.
//

#ifndef CUBE_GAME_OBJECT_HPP
#define CUBE_GAME_OBJECT_HPP

#include <glm/glm.hpp>

class Object {
public:
    virtual glm::mat4 &GetModelMatrix() = 0;
    virtual void Render() = 0;
};


#endif //CUBE_GAME_OBJECT_HPP
