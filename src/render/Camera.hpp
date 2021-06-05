//
// Created by Sarah Klocke on 05.06.21.
//

#ifndef CUBE_GAME_CAMERA_HPP
#define CUBE_GAME_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "../Direction.hpp"

class Camera {
public:
    Camera(int width, int height, float fov);

    void UpdatePerspective(int newWidth, int newHeight);
    void UpdateView();

    void Move(Direction direction, float deltaTime);
    void Tilt(float dx, float dy);

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();

private:
    void UpdateVectors();

private:
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

    float pitch;
    float yaw;
    float fov;

    int width;
    int height;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};

#endif //CUBE_GAME_CAMERA_HPP
