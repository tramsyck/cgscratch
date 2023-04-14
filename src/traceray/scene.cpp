#include "scene.h"

Scene::Scene()
{
    {
        auto light = std::make_shared<AmbientLight>(0.2);
        _lights.push_back(light);
    }
    {
        auto light = std::make_shared<PointLight>(Vector3d { 2, 1, 0 }, 0.6);
        _lights.push_back(light);
    }
    {
        auto light = std::make_shared<DirectionalLight>(Vector3d { 1, 4, 4 }, 0.2);
        _lights.push_back(light);
    }
}

void Scene::addSampleObject()
{
    {
        auto sphere = std::make_shared<Sphere>();
        sphere->center = Vector3d { 0, -1, 3 };
        sphere->radius = 1;
        sphere->color = Qt::red;
        sphere->specular = 500;
        _objects.push_back(sphere);
    }

    {
        auto sphere = std::make_shared<Sphere>();
        sphere->center = Vector3d { 2, 0, 4 };
        sphere->radius = 1;
        sphere->color = Qt::green;
        sphere->specular = 500;
        _objects.push_back(sphere);
    }

    {
        auto sphere = std::make_shared<Sphere>();
        sphere->center = Vector3d { -2, 0, 4 };
        sphere->radius = 1;
        sphere->color = Qt::blue;
        sphere->specular = 10;
        _objects.push_back(sphere);
    }
    {
        auto sphere = std::make_shared<Sphere>();
        sphere->center = Vector3d { 0, -5001, 0 };
        sphere->radius = 5000;
        sphere->color = Qt::yellow;
        sphere->specular = 1000;
        _objects.push_back(sphere);
    }
}
