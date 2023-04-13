#ifndef SCENE_H
#define SCENE_H

#include "typedefs.h"
#include <memory>
#include <vector>

#include <QtGui/QColor>
#include <light.h>
struct Sphere {
    Sphere() { }
    int radius;
    Vector3d center;
    QColor color;
};

class Scene {
public:
    Scene();

public:
    ///
    /// \brief add Sample Object
    ///
    void addSampleObject();
    std::vector<std::shared_ptr<Sphere>> getSpheres() const
    {
        return _objects;
    }
    std::vector<std::shared_ptr<Light>> getLights() const
    {
        return _lights;
    }

private:
    std::vector<std::shared_ptr<Sphere>> _objects;
    std::vector<std::shared_ptr<Light>> _lights;
};

#endif // SCENE_H
