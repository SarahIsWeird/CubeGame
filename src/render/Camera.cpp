//
// Created by Sarah Klocke on 05.06.21.
//

#include "Camera.hpp"

constexpr float SENSITIVITY = 0.1f;
constexpr float CAMERA_SPEED = 2.5f;

Camera::Camera(int width, int height, float fov)
    : width(width), height(height), fov(fov), pos(glm::vec3(0.0f, 0.0f, 3.0f)),
      front(glm::vec3(0.0f, 0.0f, 1.0f)), right(glm::vec3(0.0f)),
      up(glm::vec3(0.0f, 1.0f, 0.0f)), pitch(0.0f), yaw(-90.0f),
      viewMatrix(1.0f), projectionMatrix(1.0f) {

    this->UpdatePerspective(width, height);
    this->UpdateView();
    this->UpdateVectors();
}

void Camera::UpdatePerspective(int newWidth, int newHeight) {
    this->width = newWidth;
    this->height = newHeight;

    this->projectionMatrix = glm::perspective(
            glm::radians(45.0f),
            (float) this->width / (float) this->height,
            0.1f,
            100.0f);
}

void Camera::UpdateView() {
    this->UpdateVectors();
    this->viewMatrix = glm::lookAt(this->pos, this->pos + this->front, this->up);
}

void Camera::Move(Direction direction, float deltaTime) {
    if (direction == None) return;

    glm::vec3 tmp = glm::normalize(this->front) * CAMERA_SPEED * deltaTime;
    tmp.y = 0;

    if (direction & Forwards) this->pos += tmp;
    if (direction & Backwards) this->pos -= tmp;

    tmp = this->right * CAMERA_SPEED * deltaTime;

    if (direction & Left) this->pos -= tmp;
    if (direction & Right) this->pos += tmp;
}

void Camera::Tilt(float dx, float dy) {
    this->yaw += dx * SENSITIVITY;
    this->pitch += dy * SENSITIVITY;

    this->yaw = fmodf(this->yaw, 360.0f);
    this->pitch = glm::clamp(this->pitch, -89.99f, 89.99f);

    this->UpdateView();
}

glm::mat4 Camera::GetViewMatrix() {
    return this->viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix() {
    return this->projectionMatrix;
}

void Camera::UpdateVectors() {
    float yawRads = glm::radians(this->yaw);
    float pitchRads = glm::radians(this->pitch);

    this->front = glm::normalize(glm::vec3(cosf(yawRads) * cosf(pitchRads),
            sinf(pitchRads),
            sinf(yawRads) * cosf(pitchRads)));
    this->right = glm::normalize(glm::cross(this->front, glm::vec3(0.0f, 1.0f, 0.0f)));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}
