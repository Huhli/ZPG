#pragma once

#include <vector>

#include "DrawableObject.h"
#include "ShaderProgram.h"

class Scene
{
public:
    Scene(int sceneNumber);
    ~Scene();

    void draw();

private:
    int sceneNumber;

    ShaderProgram* shaderProgram1;
    ShaderProgram* shaderProgram2;

    Model* triangleModel;
    Model* sphereModel;
    Model* treeModel;

    DrawableObject* triangleObject;
    DrawableObject* sphereObject;

    std::vector<DrawableObject*> trees;
};