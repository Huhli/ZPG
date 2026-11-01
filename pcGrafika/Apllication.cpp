
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

    scenes.clear();

    if (window)
    {
        glfwDestroyWindow(window);
    }

    glfwTerminate();
}

void Application::initialization()
{
    // Initialize GLFW.
    if (!glfwInit())
    {
        std::cout << "GLFW initialization failed!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window.
    window = glfwCreateWindow(
        800,
        600,
        "ZPG - OpenGL 3.3",
        nullptr,
        nullptr
    );

    if (!window)
    {
        std::cout << "Window creation failed!" << std::endl;
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Initialize GLAD.
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::cout << "GLAD initialization failed!" << std::endl;
        glfwDestroyWindow(window);
        window = nullptr;
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    // Print OpenGL information.
    std::cout << "OpenGL Version: "
        << glGetString(GL_VERSION) << std::endl;

    std::cout << "Vendor: "
        << glGetString(GL_VENDOR) << std::endl;

    std::cout << "Renderer: "
        << glGetString(GL_RENDERER) << std::endl;

    std::cout << "GLSL: "
        << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // Enable depth testing.
    glEnable(GL_DEPTH_TEST);

    // Create scenes.
    scenes.push_back(new Scene(1));
    scenes.push_back(new Scene(2));
    scenes.push_back(new Scene(3));
    scenes.push_back(new Scene(4));
    scenes.push_back(new Scene(5));
    scenes.push_back(new Scene(6));

    activeScene = 1;
}

void Application::run()
{
    float lastFrame = static_cast<float>(glfwGetTime());

    double lastMouseX = 0.0;
    double lastMouseY = 0.0;
    bool wasRightMousePressed = false;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Prevent unexpectedly large movement.
        if (deltaTime > 0.1f)
        {
            deltaTime = 0.1f;
        }

        // Switch scenes using keys 1-5.
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
            activeScene = 1;

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
            activeScene = 2;

        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
            activeScene = 3;

        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
            activeScene = 4;

        if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
            activeScene = 5;

        if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
            activeScene = 6;

        // Read the current mouse position.
        double mouseX;
        double mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        bool rightMousePressed =
            glfwGetMouseButton(
                window,
                GLFW_MOUSE_BUTTON_RIGHT
            ) == GLFW_PRESS;

        // Ovládání kamery v lese (scéna 3) a solární soustavì (scéna 5).
        if (activeScene == 3 || activeScene == 5 || activeScene == 4)
        {
            Camera& camera = scenes[activeScene - 1]->getCamera();

            const float speed = 3.0f * deltaTime;

            // WASD movement.
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                camera.moveForward(speed);

            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                camera.moveForward(-speed);

            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                camera.moveRight(speed);

            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                camera.moveRight(-speed);

            // Look around while holding the right mouse button.
            if (rightMousePressed && wasRightMousePressed)
            {
                camera.rotate(
                    static_cast<float>(mouseX - lastMouseX),
                    static_cast<float>(mouseY - lastMouseY)
                );
            }
        }

        lastMouseX = mouseX;
        lastMouseY = mouseY;
        wasRightMousePressed = rightMousePressed;

        // Set the background color.
        if (activeScene == 3)
        {
            // Light blue background for the forest.
            glClearColor(0.53f, 0.78f, 0.95f, 1.0f);
        }
        else
        {
            // Keep the other scenes black.
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        }

        // Clear color and depth buffers.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the active scene.
        scenes[activeScene - 1]->draw();

        // Display the frame and process events.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
