#include <iostream>

#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb_image.h>

#include "render/Shader.hpp"
#include "render/Camera.hpp"
#include "Direction.hpp"

bool firstMouse = true;
double lastX = 400.0;
double lastY = 300.0;

Camera camera(800, 600, 90.0f); // NOLINT(cert-err58-cpp)

void processInput(GLFWwindow *win, float deltaTime) {
    if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(win, true);
    }

    int direction = None;

    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) direction += Forwards;
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) direction += Backwards;
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) direction += Left;
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) direction += Right;

    camera.Move(static_cast<Direction>(direction), deltaTime);
}

void onWindowResize(GLFWwindow *win, int width, int height) {
    glViewport(0, 0, width, height);
    camera.UpdatePerspective(width, height);
    firstMouse = true;
}

void onMouseMoved(GLFWwindow *win, double xPos, double yPos) {
    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    float dx = xPos - lastX;
    float dy = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    camera.Tilt(dx, dy);
}

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(800, 600,
                                          "Cube Game",
                                          nullptr,
                                          nullptr);

    if (!window) {
        std::cerr << "Failed to create the window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Couldn't initialize GLAD." << std::endl;
        glfwTerminate();
        return -1;
    }

    camera.UpdatePerspective(800, 600);

    glfwSetFramebufferSizeCallback(window, onWindowResize);
    glfwSetCursorPosCallback(window, onMouseMoved);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    Shader shader("shaders/vertexShader.glsl",
                  "shaders/fragmentShader.glsl");

    shader.use();

    unsigned int vbos[1];
    unsigned int vaos[1];
    unsigned int texture;

    glGenBuffers(1, vbos);
    glGenVertexArrays(1, vaos);
    glGenTextures(1, &texture);

    glBindVertexArray(vaos[0]);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);

    int texWidth, texHeight, nChannels;
    unsigned char *data = stbi_load("assets/textures/atlas.png",
                                    &texWidth, &texHeight,
                                    &nChannels,
                                    0);

    if (!data) {
        std::cerr << "Couldn't load texture atlas." << std::endl;
        glfwTerminate();
        return -1;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glm::mat4 modelMatrix = glm::mat4(1.0f);

    shader.SetModelMatrix(modelMatrix);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(0);

    double lastTime = glfwGetTime();
    double deltaTime;

    while (!glfwWindowShouldClose(window)) {
        double now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        processInput(window, deltaTime);

        camera.UpdateView();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.SetProjectionMatrix(camera.GetProjectionMatrix());
        shader.SetViewMatrix(camera.GetViewMatrix());
        modelMatrix = glm::mat4(1.0f);
        shader.SetModelMatrix(modelMatrix);

        shader.SetViewMatrix(camera.GetViewMatrix());
        shader.SetProjectionMatrix(camera.GetProjectionMatrix());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
