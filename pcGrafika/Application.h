#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Scene.h"

class Application
{
public:
    Application();
    ~Application();

    void initialization();
    void run();

private:
    GLFWwindow* window;

    std::vector<Scene*> scenes;

    int activeScene;
};