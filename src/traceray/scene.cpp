#include "scene.h"

Scene::Scene()
{
}

void Scene::addSampleObject()
{
    {
        auto sphere = std::make_shared<Sphere>();
        sphere->center = Vector3d { 0, -1, 3 };
        sphere->radius = 1;
        sphere->color = Qt::red;
        _objects.push_back(sphere);
    }

    {
        auto sphere = std::make_shared<Sphere>();
        sphere->center = Vector3d { 2, 0, 4 };
        sphere->radius = 1;
        sphere->color = Qt::green;
        _objects.push_back(sphere);
    }

    {
        auto sphere = std::make_shared<Sphere>();
        sphere->center = Vector3d { -2, 0, 4 };
        sphere->radius = 1;
        sphere->color = Qt::blue;
        _objects.push_back(sphere);
    }
}
