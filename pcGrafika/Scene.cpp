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
#include <iterator>
#include "Calipso.h"


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

    solarPhongShader = new ShaderProgram(
        "lighting_solar.vert",
        "phong_solar.frag"
    );

    sunShader = new ShaderProgram(
        "lighting_solar.vert",
        "sun_solar.frag"
    );

    // CALIPSO data is position + normal, so its normal is attribute 1.
    calipsoShader = new ShaderProgram(
        "lighting.vert",
        "calipso.frag"
    );


    // =========================
    // LIGHTING SHADERS
    // =========================

    ambientShader = new ShaderProgram(
        "lighting.vert",
        "ambient.frag"
    );

    lambertShader = new ShaderProgram(
        "lighting.vert",
        "lambert.frag"
    );

    phongShader = new ShaderProgram(
        "lighting.vert",
        "phong.frag"
    );

    blinnPhongShader = new ShaderProgram(
        "lighting.vert",
        "blinn_phong.frag"
    );

    nightShader = new ShaderProgram(
        "lighting.vert",
        "night.frag"
    );

    fireflyShader = new ShaderProgram(
        "lighting.vert",
        "firefly.frag"
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
    calipsoModel = nullptr;

    sunObject = nullptr;
    earthObject = nullptr;
    moonObject = nullptr;
    calipsoObject = nullptr;



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

    sphereModel = new Model(
        sphere,
        sizeof(sphere),
        2880,
        true,   // hasNormal
        false,  // hasColor
        false   // normalBeforeColor
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

    if (sceneNumber == 2 || sceneNumber == 3)
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

        // Remember where each hand starts in the combined vertex data.
        hourHandStart = static_cast<int>(
            filteredClock.size() / floatsPerVertex
            );

        filteredClock.insert(
            filteredClock.end(),
            std::begin(hourHandVertices),
            std::end(hourHandVertices)
        );

        minuteHandStart = static_cast<int>(
            filteredClock.size() / floatsPerVertex
            );

        filteredClock.insert(
            filteredClock.end(),
            std::begin(minuteHandVertices),
            std::end(minuteHandVertices)
        );

        secondHandStart = static_cast<int>(
            filteredClock.size() / floatsPerVertex
            );

        filteredClock.insert(
            filteredClock.end(),
            std::begin(secondHandVertices),
            std::end(secondHandVertices)
        );

        // Create one model containing the clock face and all three hands.
        clockModel = new Model(
            filteredClock.data(),
            static_cast<int>(filteredClock.size() * sizeof(float)),
            static_cast<int>(filteredClock.size() / floatsPerVertex),
            true,
            true,
            true
        );

        if (sceneNumber == 2)
        {
            clockObject = new DrawableObject(clockModel, shaderProgram1);
            clockObject->getTransformation().scaleBy(0.8f);
        }
        else if (sceneNumber == 3)
        {
            // Create two forest clock objects that share the same model.
            forestClockObject1 = new DrawableObject(clockModel, shaderProgram1);
            forestClockObject1->getTransformation().scaleBy(-0.45f);
            forestClockObject1->getTransformation().rotateZ(glm::pi<float>());
            forestClockObject1->getTransformation().translate(-5.0f, 2.0f, -7.0f);

            forestClockObject2 = new DrawableObject(clockModel, shaderProgram1);
            forestClockObject2->getTransformation().scaleBy(-0.45f);
            forestClockObject2->getTransformation().rotateZ(glm::pi<float>());
            forestClockObject2->getTransformation().translate(5.0f, 2.0f, -15.0f);
        }
    }


    // =========================
    // FOREST
    // =========================

    if (sceneNumber == 3 || sceneNumber == 4)
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
            sceneNumber == 4 ? nightShader : shaderProgram1
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
                sceneNumber == 4 ? nightShader : shaderProgram1
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

    if (sceneNumber == 4)
    {
        fireflyObject = new DrawableObject(
            sphereModel,
            fireflyShader
        );

        fireflyObject->getTransformation().scaleBy(0.07f);
        fireflyObject->getTransformation().translate(
            0.0f, 1.5f, -3.0f
        );
    }

    // =========================
    // SOLAR SYSTEM
    // =========================


    if (sceneNumber == 5)
    {
        // =========================================
        // MODELY
        // =========================================

        sunModel = new Model(
            sun, sizeof(sun), 11520, true, true
        );

        earthModel = new Model(
            earth, sizeof(earth), 11520, true, true
        );

        moonModel = new Model(
            moon, sizeof(moon), 11520, true, true
        );

        calipsoModel = new Model(
            calipso,
            sizeof(calipso),
            calipsoVertexCount,
            true,
            false,
            false
        );

        // =========================================
        // OBJEKTY A SHADERY
        // =========================================

        sunObject = new DrawableObject(
            sunModel, sunShader
        );

        earthObject = new DrawableObject(
            earthModel, solarPhongShader
        );

        moonObject = new DrawableObject(
            moonModel, solarPhongShader
        );

        calipsoObject = new DrawableObject(
            calipsoModel, calipsoShader
        );

        // =========================================
        // SLUNCE
        // =========================================

        sunObject->getTransformation().scaleBy(0.32f);

        // =========================================
        // ZEMĚ
        // =========================================

        earthScale.scaleBy(0.17f);

        // Vzdálenost Země od Slunce.
        earthOrbit.translate(0.95f, 0.0f, 0.0f);

        earthCombined.add(&earthScale);
        earthCombined.add(&earthRotation);
        earthCombined.add(&earthOrbit);

        earthObject->setTransformation(&earthCombined);

        // =========================================
        // MĚSÍC
        // =========================================

        moonScale.scaleBy(0.09f);

        // Vzdálenost Měsíce od Země.
        moonOrbit.translate(0.30f, 0.0f, 0.0f);

        moonCombined.add(&moonScale);
        moonCombined.add(&moonOrbit);
        moonCombined.add(&earthOrbit);

        moonObject->setTransformation(&moonCombined);

        // =========================================
        // DRUŽICE CALIPSO
        // =========================================

        // Zvětšené měřítko pro lepší viditelnost.
        calipsoScale.scaleBy(0.12f);

        // Poloměr oběžné dráhy kolem Země.
        calipsoOffset.translate(0.32f, 0.0f, 0.0f);

        // Naklonění oběžné roviny o 35 stupňů.
        calipsoInclination.rotateZ(
            glm::radians(35.0f)
        );

        calipsoCombined.add(&calipsoScale);
        calipsoCombined.add(&calipsoOffset);
        calipsoCombined.add(&calipsoOrbit);
        calipsoCombined.add(&calipsoInclination);
        calipsoCombined.add(&earthOrbit);

        calipsoObject->setTransformation(&calipsoCombined);
    }


    if (sceneNumber == 6)
    {
        ambientSphere = new DrawableObject(
            sphereModel, ambientShader
        );

        lambertSphere = new DrawableObject(
            sphereModel, lambertShader
        );

        phongSphere = new DrawableObject(
            sphereModel, phongShader
        );

        blinnPhongSphere = new DrawableObject(
            sphereModel, blinnPhongShader
        );

        ambientSphere->getTransformation().scaleBy(0.35f);
        ambientSphere->getTransformation().translate(-1.3f, 0.7f, 0.0f);

        lambertSphere->getTransformation().scaleBy(0.35f);
        lambertSphere->getTransformation().translate(1.3f, 0.7f, 0.0f);

        phongSphere->getTransformation().scaleBy(0.35f, 0.18f, 0.35f);
        phongSphere->getTransformation().translate(-1.3f, -0.7f, 0.0f);

        blinnPhongSphere->getTransformation().scaleBy(0.35f);
        blinnPhongSphere->getTransformation().translate(1.3f, -0.7f, 0.0f);
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
    delete calipsoObject;

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
    delete calipsoModel;


    // =========================
    // DELETE SHADERS
    // =========================

    delete shaderProgram1;
    delete shaderProgram2;

    delete ambientShader;
    delete lambertShader;
    delete phongShader;
    delete blinnPhongShader;
    delete solarPhongShader;
    delete calipsoShader;

    delete groundObject;
    delete groundModel;

    delete clockObject;
    delete forestClockObject1;
    delete forestClockObject2;
    delete clockModel;
    delete sunShader;

    delete fireflyObject;
    delete nightShader;
    delete fireflyShader;
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

        // Set the hand vertex ranges before drawing the combined clock model.
        shaderProgram1->setUniform("hourHandStart", hourHandStart);
        shaderProgram1->setUniform("minuteHandStart", minuteHandStart);
        shaderProgram1->setUniform("secondHandStart", secondHandStart);

        // Set the hand angles used by the vertex shader.
        shaderProgram1->setUniform("hourHandAngle", hourAngle);
        shaderProgram1->setUniform("minuteHandAngle", minuteAngle);
        shaderProgram1->setUniform("secondHandAngle", secondAngle);

        // Draw the combined clock model.
        clockObject->draw();

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

        // Calculate the current time for both forest clocks.
        const auto now = std::chrono::system_clock::now();
        const std::time_t currentTime =
            std::chrono::system_clock::to_time_t(now);
        std::tm localTime{};
        localtime_s(&localTime, &currentTime);

        const auto milliseconds =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                now.time_since_epoch()
            ).count() % 1000;
        const double seconds = localTime.tm_sec + milliseconds / 1000.0;
        const double minutes = localTime.tm_min + seconds / 60.0;
        const double hours = (localTime.tm_hour % 12) + minutes / 60.0;
        const double twoPi = 2.0 * std::acos(-1.0);

        const float hourAngle = static_cast<float>(-hours * twoPi / 12.0);
        const float minuteAngle = static_cast<float>(-minutes * twoPi / 60.0);
        const float secondAngle = static_cast<float>(-seconds * twoPi / 60.0);

        shaderProgram1->setUniform("hourHandStart", hourHandStart);
        shaderProgram1->setUniform("minuteHandStart", minuteHandStart);
        shaderProgram1->setUniform("secondHandStart", secondHandStart);
        shaderProgram1->setUniform("hourHandAngle", hourAngle);
        shaderProgram1->setUniform("minuteHandAngle", minuteAngle);
        shaderProgram1->setUniform("secondHandAngle", secondAngle);

        // Draw both clocks using the shared combined model.
        shaderProgram1->setUniform("useTreeColors", false);
        shaderProgram1->setUniform("useGroundColor", false);
        if (forestClockObject1 != nullptr)
            forestClockObject1->draw();
        if (forestClockObject2 != nullptr)
            forestClockObject2->draw();

        // Return to the default color mode for the signature.
        shaderProgram1->setUniform("useTreeColors", false);
        shaderProgram1->setUniform("useGroundColor", false);

        signatureLoginObject->draw();

        break;
    }

    case 4:
    {
        int width = 1;
        int height = 1;

        GLFWwindow* window = glfwGetCurrentContext();

        if (window != nullptr)
            glfwGetFramebufferSize(window, &width, &height);

        if (width <= 0) width = 1;
        if (height <= 0) height = 1;

        glViewport(0, 0, width, height);

        glm::mat4 viewMatrix = camera.getViewMatrix();

        glm::mat4 projectionMatrix = camera.getProjectionMatrix(
            static_cast<float>(width) / static_cast<float>(height)
        );

        glm::vec3 cameraPosition = camera.getPosition();

        // =====================================
        // NOČNÍ LES – BODOVÉ OSVĚTLENÍ
        // =====================================

        nightShader->use();

        nightShader->setUniform("viewMatrix", viewMatrix);
        nightShader->setUniform("projectionMatrix", projectionMatrix);

        // =====================================
        // POHYB SVĚTLUŠKY
        // =====================================

        static float fireflyAngle = 0.0f;

        // Rychlost pohybu světlušky
        fireflyAngle += 0.01f;

        // Kruhová dráha kolem středu lesa
        float fireflyX = -3.0f * sin(fireflyAngle);
        float fireflyY = 1.5f;
        float fireflyZ = -3.0f * cos(fireflyAngle);

        // Pohyb samotného modelu světlušky
        fireflyObject->getTransformation().rotateY(0.01f);

        // Aktualizace pozice bodového světla
        nightShader->setUniform(
            "lightPosition",
            fireflyX,
            fireflyY,
            fireflyZ
        );

        // Barva světla – teplá žlutá
        nightShader->setUniform(
            "lightColor", 1.0f, 0.8f, 0.25f
        );

        nightShader->setUniform(
            "viewPosition",
            cameraPosition.x,
            cameraPosition.y,
            cameraPosition.z
        );

        // Útlum světla podle vzdálenosti
        nightShader->setUniform("constantAttenuation", 1.0f);
        nightShader->setUniform("linearAttenuation", 0.09f);
        nightShader->setUniform("quadraticAttenuation", 0.032f);

        // Zem
        nightShader->setUniform(
            "objectColor", 0.12f, 0.16f, 0.08f
        );

        if (groundObject != nullptr)
            groundObject->draw();

        // Stromy
        nightShader->setUniform(
            "objectColor", 0.12f, 0.30f, 0.10f
        );

        for (DrawableObject* treeObject : trees)
        {
            treeObject->draw();
        }

        // =====================================
        // SVĚTLUŠKA
        // =====================================

        fireflyShader->use();

        fireflyShader->setUniform("viewMatrix", viewMatrix);
        fireflyShader->setUniform("projectionMatrix", projectionMatrix);

        fireflyShader->setUniform(
            "objectColor", 1.0f, 0.85f, 0.1f
        );

        if (fireflyObject != nullptr)
            fireflyObject->draw();

        break;
    }


    case 5:
    {
        int width = 1;
        int height = 1;

        GLFWwindow* window = glfwGetCurrentContext();

        if (window != nullptr)
            glfwGetFramebufferSize(window, &width, &height);

        if (width <= 0) width = 1;
        if (height <= 0) height = 1;

        glViewport(0, 0, width, height);

        // Kamera ovládaná stejně jako v lese.
        const glm::mat4 viewMatrix =
            camera.getViewMatrix();

        const glm::mat4 projectionMatrix =
            camera.getProjectionMatrix(
                static_cast<float>(width) /
                static_cast<float>(height)
            );

        const glm::vec3 cameraPosition =
            camera.getPosition();

        // =========================================
        // ANIMACE
        // =========================================

        sunObject->getTransformation().rotateY(0.003f);

        earthRotation.rotateY(0.02f);
        earthOrbit.rotateY(0.006f);

        moonOrbit.rotateY(0.025f);
        calipsoOrbit.rotateY(0.035f);

        // =========================================
        // SLUNCE
        // =========================================

        sunShader->use();

        sunShader->setUniform(
            "viewMatrix", viewMatrix
        );

        sunShader->setUniform(
            "projectionMatrix", projectionMatrix
        );

        sunObject->draw();

        // =========================================
        // ZEMĚ A MĚSÍC
        // =========================================

        solarPhongShader->use();

        solarPhongShader->setUniform(
            "viewMatrix", viewMatrix
        );

        solarPhongShader->setUniform(
            "projectionMatrix", projectionMatrix
        );

        // Světlo ve středu Slunce.
        solarPhongShader->setUniform(
            "lightPosition", 0.0f, 0.0f, 0.0f
        );

        solarPhongShader->setUniform(
            "lightColor", 1.0f, 0.88f, 0.68f
        );

        solarPhongShader->setUniform(
            "viewPosition",
            cameraPosition.x,
            cameraPosition.y,
            cameraPosition.z
        );

        // Země.
        solarPhongShader->setUniform(
            "objectColor", 1.0f, 1.0f, 1.0f
        );

        earthObject->draw();

        // Měsíc.
        solarPhongShader->setUniform(
            "objectColor", 1.0f, 1.0f, 1.0f
        );

        moonObject->draw();

        // =========================================
        // CALIPSO
        // =========================================

        // POZOR: CALIPSO používá vlastní calipsoShader.
        calipsoShader->use();


        calipsoShader->setUniform(
            "viewMatrix", viewMatrix
        );

        calipsoShader->setUniform(
            "projectionMatrix", projectionMatrix
        );

        calipsoShader->setUniform(
            "lightPosition", 0.0f, 0.0f, 0.0f
        );

        calipsoShader->setUniform(
            "lightColor", 1.0f, 0.95f, 0.75f
        );

        calipsoShader->setUniform(
            "viewPosition",
            cameraPosition.x,
            cameraPosition.y,
            cameraPosition.z
        );

        calipsoShader->setUniform(
            "objectColor", 1.0f, 0.85f, 0.25f
        );

        calipsoObject->draw();

        break;
    }

    case 6:
    {
        bool badViewport = false;

        int width = 1;
        int height = 1;

        GLFWwindow* window = glfwGetCurrentContext();

        if (window != nullptr) {
            glfwGetFramebufferSize(window, &width, &height);
        }

        if (width <= 0) width = 1;
        if (height <= 0) height = 1;

        if (badViewport)
        {
            // Záměrně špatný viewport – používá původní rozměry.
            glViewport(0, 0, 800, 600);
        }
        else
        {
            // Správný viewport podle aktuální velikosti okna.
            glViewport(0, 0, width, height);
        }

        glm::mat4 viewMatrix = glm::lookAt(
            glm::vec3(0.0f, 0.0f, 4.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        glm::mat4 projectionMatrix;

        if (badViewport)
        {
            // CHYBNĚ – poměr stran je vždy 1:1.
            projectionMatrix = glm::perspective(
                glm::radians(45.0f),
                1.0f,
                0.1f,
                100.0f
            );
        }
        else
        {
            // SPRÁVNĚ – poměr stran odpovídá oknu.
            projectionMatrix = glm::perspective(
                glm::radians(45.0f),
                static_cast<float>(width) / static_cast<float>(height),
                0.1f,
                100.0f
            );
        }

        // Ambient
        ambientShader->use();
        ambientShader->setUniform("normalMode", 2);
        ambientShader->setUniform("viewMatrix", viewMatrix);
        ambientShader->setUniform("projectionMatrix", projectionMatrix);
        ambientShader->setUniform(
            "objectColor", 1.0f, 0.8f, 0.1f
        );
        ambientSphere->draw();

        // Lambert - chybná transformace normál
        lambertShader->use();
        lambertShader->setUniform("normalMode", 1);
        lambertShader->setUniform("viewMatrix", viewMatrix);
        lambertShader->setUniform("projectionMatrix", projectionMatrix);
        lambertShader->setUniform(
            "objectColor", 0.2f, 0.5f, 1.0f
        );
        lambertShader->setUniform(
            "lightPosition", 0.0f, 0.0f, 0.0f
        );
        lambertSphere->draw();

        // Phong - správná transformace normál
        phongShader->use();
        phongShader->setUniform("normalMode", 2);
        phongShader->setUniform("viewMatrix", viewMatrix);
        phongShader->setUniform("projectionMatrix", projectionMatrix);
        phongShader->setUniform(
            "objectColor", 1.0f, 0.2f, 0.2f
        );
        phongShader->setUniform(
            "lightPosition", 0.0f, 0.0f, 0.0f
        );
        phongShader->setUniform(
            "viewPosition", 0.0f, 0.0f, 4.0f
        );
        phongShader->setUniform("shininess", 1.0f);
        phongSphere->draw();

        // Blinn-Phong - správná transformace normál
        blinnPhongShader->use();
        blinnPhongShader->setUniform("normalMode", 2);
        blinnPhongShader->setUniform("viewMatrix", viewMatrix);
        blinnPhongShader->setUniform("projectionMatrix", projectionMatrix);
        blinnPhongShader->setUniform(
            "objectColor", 0.2f, 1.0f, 0.3f
        );
        blinnPhongShader->setUniform(
            "lightPosition", 0.0f, 0.0f, 0.0f
        );
        blinnPhongShader->setUniform(
            "viewPosition", 0.0f, 0.0f, 4.0f
        );
        blinnPhongSphere->draw();

        break;
    }
    }


}

Camera& Scene::getCamera()
{
    return camera;
}