#include "Scene.h"

#include "sphere.h"
#include "triangle.h"
#include "tree.h"


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

    triangleObject = nullptr;
    sphereObject = nullptr;


    // =========================
    // TRIANGLE
    // =========================

    triangleModel =
        new Model(
            triangle,
            sizeof(triangle),
            3,
            false
        );

    triangleObject =
        new DrawableObject(
            triangleModel,
            shaderProgram2
        );


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
    // FOREST
    // =========================

    if (sceneNumber == 3)
    {
        treeModel =
            new Model(
                tree,
                sizeof(tree),
                92814,
                true
            );


        // Tree 1
        DrawableObject* tree1 =
            new DrawableObject(
                treeModel,
                shaderProgram1
            );

        tree1->getTransformation().scaleBy(0.12f);
        tree1->getTransformation().translate(-0.9f, -0.8f, 0.0f);

        trees.push_back(tree1);


        // Tree 2
        DrawableObject* tree2 =
            new DrawableObject(
                treeModel,
                shaderProgram1
            );

        tree2->getTransformation().scaleBy(0.14f);
        tree2->getTransformation().translate(-0.6f, -0.8f, 0.0f);

        trees.push_back(tree2);


        // Tree 3
        DrawableObject* tree3 =
            new DrawableObject(
                treeModel,
                shaderProgram1
            );

        tree3->getTransformation().scaleBy(0.10f);
        tree3->getTransformation().translate(-0.3f, -0.8f, 0.0f);

        trees.push_back(tree3);


        // Tree 4
        DrawableObject* tree4 =
            new DrawableObject(
                treeModel,
                shaderProgram1
            );

        tree4->getTransformation().scaleBy(0.13f);
        tree4->getTransformation().translate(0.0f, -0.8f, 0.0f);

        trees.push_back(tree4);


        // Tree 5
        DrawableObject* tree5 =
            new DrawableObject(
                treeModel,
                shaderProgram1
            );

        tree5->getTransformation().scaleBy(0.11f);
        tree5->getTransformation().translate(0.3f, -0.8f, 0.0f);

        trees.push_back(tree5);


        // Tree 6
        DrawableObject* tree6 =
            new DrawableObject(
                treeModel,
                shaderProgram1
            );

        tree6->getTransformation().scaleBy(0.15f);
        tree6->getTransformation().translate(0.6f, -0.8f, 0.0f);

        trees.push_back(tree6);


        // Tree 7
        DrawableObject* tree7 =
            new DrawableObject(
                treeModel,
                shaderProgram1
            );

        tree7->getTransformation().scaleBy(0.12f);
        tree7->getTransformation().translate(0.9f, -0.8f, 0.0f);

        trees.push_back(tree7);


        // Tree 8
        DrawableObject* tree8 =
            new DrawableObject(
                treeModel,
                shaderProgram1
            );

        tree8->getTransformation().scaleBy(0.09f);
        tree8->getTransformation().translate(-0.75f, -0.2f, 0.0f);

        trees.push_back(tree8);


        // Tree 9
        DrawableObject* tree9 =
            new DrawableObject(
                treeModel,
                shaderProgram1
            );

        tree9->getTransformation().scaleBy(0.11f);
        tree9->getTransformation().translate(-0.25f, -0.2f, 0.0f);

        trees.push_back(tree9);


        // Tree 10
        DrawableObject* tree10 =
            new DrawableObject(
                treeModel,
                shaderProgram1
            );

        tree10->getTransformation().scaleBy(0.10f);
        tree10->getTransformation().translate(0.25f, -0.2f, 0.0f);

        trees.push_back(tree10);


        // Tree 11
        DrawableObject* tree11 =
            new DrawableObject(
                treeModel,
                shaderProgram1
            );

        tree11->getTransformation().scaleBy(0.13f);
        tree11->getTransformation().translate(0.75f, -0.2f, 0.0f);

        trees.push_back(tree11);


        // Tree 12
        DrawableObject* tree12 =
            new DrawableObject(
                treeModel,
                shaderProgram1
            );

        tree12->getTransformation().scaleBy(0.08f);
        tree12->getTransformation().translate(0.0f, 0.25f, 0.0f);

        trees.push_back(tree12);
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


    // =========================
    // DELETE MODELS
    // =========================

    delete triangleModel;
    delete sphereModel;
    delete treeModel;


    // =========================
    // DELETE SHADERS
    // =========================

    delete shaderProgram1;
    delete shaderProgram2;
}


void Scene::draw()
{
    switch (sceneNumber)
    {
    case 1:
        triangleObject->draw();
        break;


    case 2:
        sphereObject->draw();
        break;


    case 3:

        for (DrawableObject* treeObject : trees)
        {
            treeObject->draw();
        }

        break;


    case 4:
        // Login will be added later
        break;
    }
}