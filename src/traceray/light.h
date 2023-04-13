
#ifndef LIGHT_H
#define LIGHT_H

#include "typedefs.h"
class Light {
public:
    enum LightType {
        Ambient,
        Point,
        Directional
    };

public:
    Light(LightType t, double intensity)
        : _type(t)
        , _intensity(intensity)
    {
    }

    LightType getType() { return _type; }

    double getIntensity() { return _intensity; }

private:
    LightType _type;
    double _intensity;
};

class AmbientLight : public Light {
public:
    AmbientLight(double intensity)
        : Light(Ambient, intensity)
    {
    }
};

class PointLight : public Light {
public:
    PointLight(const Vector3d& pos, double intensity)
        : Light(Point, intensity)
        , _position(pos)
    {
    }

    Vector3d position() { return _position; }

private:
    Vector3d _position;
};

class DirectionalLight : public Light {
public:
    DirectionalLight(const Vector3d& pos, double intensity)
        : Light(Directional, intensity)
        , _position(pos)
    {
    }

    Vector3d position() { return _position; }

private:
    Vector3d _position;
};

#endif // LIGHT_H
