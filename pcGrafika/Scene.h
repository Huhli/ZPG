#pragma once

#include <vector>

#include "DrawableObject.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include <memory>
#include "sun.h"
#include "earth.h"
#include "moon.h"
#include "Camera.h"

class Scene
{
public:
    Scene(int sceneNumber);
    ~Scene();

    void draw();
    Camera& getCamera();

private:
    int sceneNumber;

    ShaderProgram* shaderProgram1;
    ShaderProgram* shaderProgram2;

    Model* triangleModel;
    Model* sphereModel;
    Model* treeModel;
    Model* loginModel;
    Model* signatureLoginModel;

    DrawableObject* triangleObject;
    DrawableObject* sphereObject;
    DrawableObject* loginObject;
    DrawableObject* signatureLoginObject;

    // Transformations for the triangle
    Transformation triangleMove;
    Transformation triangleRotation;
    CompositeTransformation triangleCombined;

    std::vector<DrawableObject*> trees;
    std::vector<std::unique_ptr<Transformation>> treeTransformations;
    std::vector<std::unique_ptr<CompositeTransformation>> treeComposites;

    // Solar system models
    Model* sunModel;
    Model* earthModel;
    Model* moonModel;

    // Solar system objects
    DrawableObject* sunObject;
    DrawableObject* earthObject;
    DrawableObject* moonObject;

    // Solar system transformations
    Transformation earthOrbit;
    Transformation earthScale;
    Transformation moonOrbit;
    Transformation moonScale;

    CompositeTransformation earthOrbitCombined;
    CompositeTransformation earthCombined;
    CompositeTransformation moonCombined;

    Camera camera;

    Model* groundModel = nullptr;
    DrawableObject* groundObject = nullptr;

    Model* clockModel = nullptr;
    DrawableObject* clockObject = nullptr;

    Model* hourHandModel = nullptr;
    Model* minuteHandModel = nullptr;
    Model* secondHandModel = nullptr;

    DrawableObject* hourHandObject = nullptr;
    DrawableObject* minuteHandObject = nullptr;
    DrawableObject* secondHandObject = nullptr;

    Transformation hourHandRotation;
    Transformation minuteHandRotation;
    Transformation secondHandRotation;

    double previousHourAngle = 0.0;
    double previousMinuteAngle = 0.0;
    double previousSecondAngle = 0.0;

    CompositeTransformation hourHandCombined;
    CompositeTransformation minuteHandCombined;
    CompositeTransformation secondHandCombined;
};