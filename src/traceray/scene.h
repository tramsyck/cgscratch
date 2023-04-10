#ifndef SCENE_H
#define SCENE_H

#include "typedefs.h"
#include <memory>
#include <vector>

#include <QtGui/QColor>

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

private:
    std::vector<std::shared_ptr<Sphere>> _objects;
};

#endif // SCENE_H
