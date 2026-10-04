#include "Application.h"

#include <iostream>
#include <cstdlib>


Application::Application()
{
    window = nullptr;
    activeScene = 1;
}

Application::~Application()
{
    for (Scene* scene : scenes)
    {
        delete scene;
    }

    if (window)
    {
        glfwDestroyWindow(window);
    }

    glfwTerminate();
}


void Application::initialization()
{
    // =========================
    // GLFW
    // =========================

    if (!glfwInit())
    {
        std::cout
            << "GLFW initialization failed!"
            << std::endl;

        exit(EXIT_FAILURE);
    }


    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MAJOR,
        3
    );

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MINOR,
        3
    );

    glfwWindowHint(
        GLFW_OPENGL_FORWARD_COMPAT,
        GL_TRUE
    );

    glfwWindowHint(
        GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE
    );


    // =========================
    // WINDOW
    // =========================

    window = glfwCreateWindow(
        800,
        600,
        "ZPG - OpenGL 3.3",
        NULL,
        NULL
    );


    if (!window)
    {
        std::cout
            << "Window creation failed!"
            << std::endl;

        glfwTerminate();

        exit(EXIT_FAILURE);
    }


    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);


    // =========================
    // GLAD
    // =========================

    if (!gladLoadGL(
        (GLADloadfunc)glfwGetProcAddress
    ))
    {
        std::cout
            << "GLAD initialization failed!"
            << std::endl;

        glfwTerminate();

        exit(EXIT_FAILURE);
    }


    // =========================
    // OPENGL INFO
    // =========================

    std::cout
        << "OpenGL Version: "
        << glGetString(GL_VERSION)
        << std::endl;

    std::cout
        << "Vendor: "
        << glGetString(GL_VENDOR)
        << std::endl;

    std::cout
        << "Renderer: "
        << glGetString(GL_RENDERER)
        << std::endl;

    std::cout
        << "GLSL: "
        << glGetString(GL_SHADING_LANGUAGE_VERSION)
        << std::endl;


    // =========================
    // DEPTH
    // =========================

    glEnable(GL_DEPTH_TEST);


    // =========================
    // SCENE
    // =========================

    scenes.push_back(new Scene(1));
    scenes.push_back(new Scene(2));
    scenes.push_back(new Scene(3));
    scenes.push_back(new Scene(4));

    activeScene = 1;
}


void Application::run()
{
    while (!glfwWindowShouldClose(window))
    {
        // =========================
        // SCENE SWITCHING
        // =========================

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        {
            activeScene = 1;
        }

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        {
            activeScene = 2;
        }

        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        {
            activeScene = 3;
        }

        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        {
            activeScene = 4;
        }


        // =========================
        // CLEAR
        // =========================

        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );


        // =========================
        // DRAW ACTIVE SCENE
        // =========================

        scenes[activeScene - 1]->draw();


        // =========================
        // DISPLAY
        // =========================

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}