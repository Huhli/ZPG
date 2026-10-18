#include "Scene.h"

#include "sphere.h"
#include "triangle.h"
#include "tree.h"
#include "VAL0527.h"
#include "clock.h"
#include <cstdlib>
#include <ctime>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <chrono>
#include <cmath>
#include <vector>


Scene::Scene(int sceneNumber)
{
    this->sceneNumber = sceneNumber;

    // =========================
    // SHADER PROGRAMS
    // =========================

    shaderProgram1 =
        new ShaderProgram(
            "shaders/basic.vert",
            "shaders/basic.frag"
        );

    shaderProgram2 =
        new ShaderProgram(
            "square.vert",
            "square.frag"
        );


    // =========================
    // INITIALIZE POINTERS
    // =========================

    triangleModel = nullptr;
    sphereModel = nullptr;
    treeModel = nullptr;
    loginModel = nullptr;
    signatureLoginModel = nullptr;

    triangleObject = nullptr;
    sphereObject = nullptr;
    loginObject = nullptr;
    signatureLoginObject = nullptr;

    sunModel = nullptr;
    earthModel = nullptr;
    moonModel = nullptr;

    sunObject = nullptr;
    earthObject = nullptr;
    moonObject = nullptr;


    // =========================
    // TRIANGLE
    // =========================

    triangleModel =
        new Model(
            triangle,
            sizeof(triangle),
            3,
            false,
            true
        );

    triangleObject =
        new DrawableObject(
            triangleModel,
            shaderProgram2
        );

    // Composite transformation for the triangle
    triangleMove.translate(0.5f, 0.0f, 0.0f);
    triangleRotation.rotateY(0.5f);

    triangleCombined.add(&triangleMove);
    triangleCombined.add(&triangleRotation);

    triangleObject->setTransformation(&triangleCombined);


    // =========================
    // SPHERE
    // =========================

    sphereModel =
        new Model(
            sphere,
            sizeof(sphere),
            2880,
            true
        );

    sphereObject =
        new DrawableObject(
            sphereModel,
            shaderProgram1
        );

    sphereObject->getTransformation().scaleBy(0.5f);

    sphereObject->getTransformation().translate(
        -0.45f,
        0.0f,
        0.0f
    );

    // =========================
    // LOGIN + SIGNATURE
    // =========================
    loginModel = new Model(
        VAL0527,
        sizeof(VAL0527),
        VAL0527_VERTEX_COUNT,
        true
    );
    loginObject =
        new DrawableObject(
            loginModel,
            shaderProgram1
        );
    loginObject->getTransformation().scaleBy(0.5f);


    signatureLoginModel =
        new Model(
            VAL0527,
            sizeof(VAL0527),
            VAL0527_VERTEX_COUNT,
            true
        );

    signatureLoginObject =
        new DrawableObject(
            signatureLoginModel,
            shaderProgram1
        );

    signatureLoginObject->getTransformation().scaleBy(0.09f);

    signatureLoginObject->getTransformation().translate(
        0.82f,
        -0.86f,
        0.0f
    );

    if (sceneNumber == 2)
    {
        const glm::vec3 logoColor(
            20.0f / 255.0f,
            184.0f / 255.0f,
            196.0f / 255.0f
        );

        // Filter out the unwanted red, green and blue geometry.
        std::vector<float> filteredClock;
        filteredClock.reserve(sizeof(::clockModel) / sizeof(float));

        const size_t floatsPerVertex = 9;
        const size_t verticesPerTriangle = 3;
        const size_t floatsPerTriangle =
            floatsPerVertex * verticesPerTriangle;

        for (size_t i = 0; i < ::vertexCount; i += verticesPerTriangle)
        {
            const size_t start = i * floatsPerVertex;

            const float* v1 = &::clockModel[start];
            const float* v2 = &::clockModel[start + floatsPerVertex];
            const float* v3 = &::clockModel[start + 2 * floatsPerVertex];

            auto isPrimaryColor = [](const float* vertex)
                {
                    const float r = vertex[6];
                    const float g = vertex[7];
                    const float b = vertex[8];

                    const bool red =
                        r > 0.9f && g < 0.1f && b < 0.1f;

                    const bool green =
                        r < 0.1f && g > 0.9f && b < 0.1f;

                    const bool blue =
                        r < 0.1f && g < 0.1f && b > 0.9f;

                    return red || green || blue;
                };

            // Skip triangles whose vertices all have the same primary color.
            if (isPrimaryColor(v1) &&
                isPrimaryColor(v2) &&
                isPrimaryColor(v3) &&
                v1[6] == v2[6] && v1[6] == v3[6] &&
                v1[7] == v2[7] && v1[7] == v3[7] &&
                v1[8] == v2[8] && v1[8] == v3[8])
            {
                continue;
            }

            filteredClock.insert(
                filteredClock.end(),
                ::clockModel + start,
                ::clockModel + start + floatsPerTriangle
            );
        }

        // Change yellow clock elements to turquoise.
        const float turquoiseR = 20.0f / 255.0f;
        const float turquoiseG = 184.0f / 255.0f;
        const float turquoiseB = 196.0f / 255.0f;

        for (size_t i = 0; i < filteredClock.size(); i += floatsPerVertex)
        {
            float& r = filteredClock[i + 6];
            float& g = filteredClock[i + 7];
            float& b = filteredClock[i + 8];

            // Detect yellow vertices.
            if (r > 0.9f && g > 0.9f && b < 0.1f)
            {
                r = turquoiseR;
                g = turquoiseG;
                b = turquoiseB;
            }
        }

        // Create the model after filtering and changing colors.
        clockModel = new Model(
            filteredClock.data(),
            static_cast<int>(filteredClock.size() * sizeof(float)),
            static_cast<int>(filteredClock.size() / floatsPerVertex),
            true,
            true,
            true
        );

        clockObject = new DrawableObject(
            clockModel,
            shaderProgram1
        );

        clockObject->getTransformation().scaleBy(0.8f);
  

        // =========================
// CLOCK HANDS
// =========================

// Hour hand: short and wide.
        const float hourHandVertices[] = {
            // Position             Normal          Color
            -0.0175f, 0.0f, -0.07f,  0, 0, -1,      0.08f, 0.08f, 0.08f,
             0.0175f, 0.0f, -0.07f,  0, 0, -1,      0.08f, 0.08f, 0.08f,
             0.0125f, 0.40f, -0.07f, 0, 0, -1,     0.08f, 0.08f, 0.08f,

            -0.0175f, 0.0f, -0.07f,  0, 0, -1,      0.08f, 0.08f, 0.08f,
             0.0125f, 0.40f, -0.07f, 0, 0, -1,     0.08f, 0.08f, 0.08f,
            -0.0125f, 0.40f, -0.07f, 0, 0, -1,     0.08f, 0.08f, 0.08f
        };

        // Minute hand: longer and thinner.
        const float minuteHandVertices[] = {
            -0.011f, 0.0f, -0.075f, 0, 0, -1,      0.10f, 0.10f, 0.10f,
             0.011f, 0.0f, -0.075f, 0, 0, -1,      0.10f, 0.10f, 0.10f,
             0.007f, 0.58f, -0.075f, 0, 0, -1,     0.10f, 0.10f, 0.10f,

            -0.011f, 0.0f, -0.075f, 0, 0, -1,      0.10f, 0.10f, 0.10f,
             0.007f, 0.58f, -0.075f, 0, 0, -1,     0.10f, 0.10f, 0.10f,
            -0.007f, 0.58f, -0.075f, 0, 0, -1,     0.10f, 0.10f, 0.10f
        };

        // Second hand: very thin and long.
        const float secondHandVertices[] = {
            -0.006f, 0.0f, -0.08f, 0, 0, -1,        0.85f, 0.05f, 0.05f,
             0.006f, 0.0f, -0.08f, 0, 0, -1,        0.85f, 0.05f, 0.05f,
             0.004f, 0.70f, -0.08f, 0, 0, -1,       0.85f, 0.05f, 0.05f,

            -0.006f, 0.0f, -0.08f, 0, 0, -1,        0.85f, 0.05f, 0.05f,
             0.004f, 0.70f, -0.08f, 0, 0, -1,       0.85f, 0.05f, 0.05f,
            -0.004f, 0.70f, -0.08f, 0, 0, -1,      0.85f, 0.05f, 0.05f
        };

        // Create the hand models.
        hourHandModel = new Model(
            hourHandVertices,
            sizeof(hourHandVertices),
            6,
            true,
            true,
            true
        );

        minuteHandModel = new Model(
            minuteHandVertices,
            sizeof(minuteHandVertices),
            6,
            true,
            true,
            true
        );

        secondHandModel = new Model(
            secondHandVertices,
            sizeof(secondHandVertices),
            6,
            true,
            true,
            true
        );

        // Create the drawable objects.
        hourHandObject = new DrawableObject(hourHandModel, shaderProgram1);
        minuteHandObject = new DrawableObject(minuteHandModel, shaderProgram1);
        secondHandObject = new DrawableObject(secondHandModel, shaderProgram1);

        // Connect the rotations to the composite transformations.
        hourHandCombined.add(&hourHandRotation);
        minuteHandCombined.add(&minuteHandRotation);
        secondHandCombined.add(&secondHandRotation);

        hourHandObject->setTransformation(&hourHandCombined);
        minuteHandObject->setTransformation(&minuteHandCombined);
        secondHandObject->setTransformation(&secondHandCombined);
    }


      // =========================
      // FOREST
      // =========================

    if (sceneNumber == 3)
    {
        // =========================
        // FOREST GROUND
        // =========================

        const float groundVertices[] = {
            // Position             Normal
            -50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,
             50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,
             50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f,

            -50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,
             50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f,
            -50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f
        };

        groundModel = new Model(
            groundVertices,
            sizeof(groundVertices),
            6,
            true
        );

        groundObject = new DrawableObject(
            groundModel,
            shaderProgram1
        );


        treeModel = new Model(
            tree,
            sizeof(tree),
            92814,
            true
        );

        // Initialize random number generation.
        static bool randomInitialized = false;

        if (!randomInitialized)
        {
            std::srand(
                static_cast<unsigned int>(std::time(nullptr))
            );
            randomInitialized = true;
        }

        const int treeCount = 80;

        for (int i = 0; i < treeCount; ++i)
        {
            DrawableObject* treeObject = new DrawableObject(
                treeModel,
                shaderProgram1
            );

            // Random position in the 3D forest.
            float x = -10.0f
                + static_cast<float>(std::rand()) / RAND_MAX * 20.0f;

            float z = -20.0f
                + static_cast<float>(std::rand()) / RAND_MAX * 22.0f;

            // Random tree size.
            float scale = 0.2f
                + static_cast<float>(std::rand()) / RAND_MAX * 0.2f;

            // Keep the transformations alive.
            auto scaleTransformation = std::make_unique<Transformation>();
            scaleTransformation->scaleBy(scale);

            auto positionTransformation = std::make_unique<Transformation>();
            positionTransformation->translate(x, 0.0f, z);

            auto composite = std::make_unique<CompositeTransformation>();
            composite->add(scaleTransformation.get());
            composite->add(positionTransformation.get());

            treeObject->setTransformation(composite.get());

            treeTransformations.push_back(std::move(scaleTransformation));
            treeTransformations.push_back(std::move(positionTransformation));
            treeComposites.push_back(std::move(composite));

            trees.push_back(treeObject);
        }
    }

      // =========================
      // SOLAR SYSTEM
      // =========================

      if (sceneNumber == 5)
      {
          sunModel = new Model(sun, sizeof(sun), 11520, true, true);
          earthModel = new Model(earth, sizeof(earth), 11520, true, true);
          moonModel = new Model(moon, sizeof(moon), 11520, true, true);

          sunObject = new DrawableObject(sunModel, shaderProgram1);
          earthObject = new DrawableObject(earthModel, shaderProgram1);
          moonObject = new DrawableObject(moonModel, shaderProgram1);

          // Scale the Sun.
          sunObject->getTransformation().scaleBy(0.25f);

          // Prepare the Earth's orbit around the Sun.
          earthScale.scaleBy(0.13f);
          earthOrbit.translate(0.65f, 0.0f, 0.0f);

          earthCombined.add(&earthScale);
          earthCombined.add(&earthOrbit);
          earthObject->setTransformation(&earthCombined);

          // Prepare the Moon's orbit around the Earth.
          moonScale.scaleBy(0.07f);
          moonOrbit.translate(0.25f, 0.0f, 0.0f);

          moonCombined.add(&moonScale);
          moonCombined.add(&moonOrbit);
          moonCombined.add(&earthOrbit);

          moonObject->setTransformation(&moonCombined);
      
      }
}


Scene::~Scene()
{
    // =========================
    // DELETE TREE OBJECTS
    // =========================

    for (DrawableObject* treeObject : trees)
    {
        delete treeObject;
    }

    trees.clear();


    // =========================
    // DELETE OBJECTS
    // =========================

    delete triangleObject;
    delete sphereObject;
    delete loginObject;
    delete signatureLoginObject;
    delete sunObject;
    delete earthObject;
    delete moonObject;

    // =========================
    // DELETE MODELS
    // =========================

    delete triangleModel;
    delete sphereModel;
    delete treeModel;
    delete loginModel;
    delete signatureLoginModel;
    delete sunModel;
    delete earthModel;
    delete moonModel;


    // =========================
    // DELETE SHADERS
    // =========================

    delete shaderProgram1;
    delete shaderProgram2;

    delete groundObject;
    delete groundModel;

    delete clockObject;
    delete clockModel;

    delete hourHandObject;
    delete minuteHandObject;
    delete secondHandObject;

    delete hourHandModel;
    delete minuteHandModel;
    delete secondHandModel;
}


void Scene::draw()
{
    switch (sceneNumber)
    {
    case 1:
        triangleRotation.rotateZ(0.5f);
        triangleObject->draw();

        // Small signature
        signatureLoginObject->draw();
        break;


    case 2:
    {
        shaderProgram1->use();

        shaderProgram1->setUniform(
            "viewMatrix",
            glm::mat4(1.0f)
        );

        shaderProgram1->setUniform(
            "projectionMatrix",
            glm::mat4(1.0f)
        );

        shaderProgram1->setUniform("useTreeColors", false);
        shaderProgram1->setUniform("useGroundColor", false);

        // Get the current local system time.
        const auto now = std::chrono::system_clock::now();
        const std::time_t currentTime =
            std::chrono::system_clock::to_time_t(now);

        std::tm localTime{};

        localtime_s(&localTime, &currentTime);

        // Get milliseconds for a smoothly moving second hand.
        const auto milliseconds =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                now.time_since_epoch()
            ).count() % 1000;

        const double seconds =
            localTime.tm_sec + milliseconds / 1000.0;

        const double minutes =
            localTime.tm_min + seconds / 60.0;

        const double hours =
            (localTime.tm_hour % 12) + minutes / 60.0;

        const double twoPi = 2.0 * std::acos(-1.0);

        const float hourAngle = static_cast<float>(
            -hours * twoPi / 12.0
            );

        const float minuteAngle = static_cast<float>(
            -minutes * twoPi / 60.0
            );

        const float secondAngle = static_cast<float>(
            -seconds * twoPi / 60.0
            );

        // Reset each transformation before applying the new angle.
        hourHandRotation = Transformation();
        minuteHandRotation = Transformation();
        secondHandRotation = Transformation();

        hourHandRotation.rotateZ(hourAngle);
        minuteHandRotation.rotateZ(minuteAngle);
        secondHandRotation.rotateZ(secondAngle);

        // Draw the clock face first.
        clockObject->draw();

        // Draw the hands independently.
        hourHandObject->draw();
        minuteHandObject->draw();
        secondHandObject->draw();

        signatureLoginObject->draw();

        break;
    }

    case 3:
    {
        int width;
        int height;

        GLFWwindow* window = glfwGetCurrentContext();
        glfwGetFramebufferSize(window, &width, &height);

        if (height == 0)
            height = 1;

        shaderProgram1->use();

        // Set camera matrices before drawing anything.
        shaderProgram1->setUniform(
            "viewMatrix",
            camera.getViewMatrix()
        );

        shaderProgram1->setUniform(
            "projectionMatrix",
            camera.getProjectionMatrix(
                static_cast<float>(width) / height
            )
        );

        // Draw the ground first.
        shaderProgram1->setUniform("useTreeColors", false);
        shaderProgram1->setUniform("useGroundColor", true);

        if (groundObject != nullptr)
        {
            groundObject->draw();
        }

        // Draw all trees.
        shaderProgram1->setUniform("useGroundColor", false);
        shaderProgram1->setUniform("useTreeColors", true);

        for (DrawableObject* treeObject : trees)
        {
            treeObject->draw();
        }

        // Return to the default color mode for the signature.
        shaderProgram1->setUniform("useTreeColors", false);
        shaderProgram1->setUniform("useGroundColor", false);

        signatureLoginObject->draw();

        break;
    }

    case 4:
        loginObject->getTransformation().rotateY(0.01f);
        loginObject->draw();
        break;

    case 5:
        earthOrbit.rotateY(0.006f);
        moonOrbit.rotateY(0.025f);

        sunObject->draw();
        earthObject->draw();
        moonObject->draw();
        break;
    }

}

Camera& Scene::getCamera()
{
    return camera;
}