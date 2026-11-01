#pragma once

#include <vector>
#include <memory>

#include "DrawableObject.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
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


    ShaderProgram* ambientShader = nullptr;
    ShaderProgram* lambertShader = nullptr;
    ShaderProgram* phongShader = nullptr;
    ShaderProgram* blinnPhongShader = nullptr;
    ShaderProgram* solarPhongShader = nullptr;
    ShaderProgram* calipsoShader = nullptr;
    ShaderProgram* sunShader = nullptr;

    DrawableObject* ambientSphere = nullptr;
    DrawableObject* lambertSphere = nullptr;
    DrawableObject* phongSphere = nullptr;
    DrawableObject* blinnPhongSphere = nullptr;


    Model* triangleModel;
    Model* sphereModel;
    Model* treeModel;
    Model* loginModel;
    Model* signatureLoginModel;

    DrawableObject* triangleObject;
    DrawableObject* sphereObject;
    DrawableObject* loginObject;
    DrawableObject* signatureLoginObject;

    // Transformations for the triangle.
    Transformation triangleMove;
    Transformation triangleRotation;
    CompositeTransformation triangleCombined;

    std::vector<DrawableObject*> trees;
    std::vector<std::unique_ptr<Transformation>> treeTransformations;
    std::vector<std::unique_ptr<CompositeTransformation>> treeComposites;

    // Solar system models.
    Model* sunModel;
    Model* earthModel;
    Model* moonModel;
    Model* calipsoModel = nullptr;

    // Solar system objects.
    DrawableObject* sunObject;
    DrawableObject* earthObject;
    DrawableObject* moonObject;
    DrawableObject* calipsoObject = nullptr;

    // Solar system transformations.
    Transformation earthOrbit;
    Transformation earthScale;
    Transformation moonOrbit;
    Transformation moonScale;
    Transformation calipsoScale;
    Transformation calipsoOffset;
    Transformation calipsoOrbit;
    Transformation calipsoInclination;

    Transformation sunRotation;
    Transformation earthRotation;

    CompositeTransformation earthOrbitCombined;
    CompositeTransformation earthCombined;
    CompositeTransformation moonCombined;
    CompositeTransformation calipsoCombined;

    Camera camera;

    Model* groundModel = nullptr;
    DrawableObject* groundObject = nullptr;

    // One combined clock model, reused in both scenes.
    Model* clockModel = nullptr;
    DrawableObject* clockObject = nullptr;
    DrawableObject* forestClockObject1 = nullptr;
    DrawableObject* forestClockObject2 = nullptr;

    // Vertex indices of the hands in the combined clock model.
    int hourHandStart = 0;
    int minuteHandStart = 0;
    int secondHandStart = 0;

    ShaderProgram* nightShader = nullptr;
    ShaderProgram* fireflyShader = nullptr;
    DrawableObject* fireflyObject = nullptr;
    Transformation fireflyMovement;
};
