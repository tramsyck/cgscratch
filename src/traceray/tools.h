#ifndef TOOLS_H
#define TOOLS_H

#include "canvas.h"
#include "typedefs.h"
namespace tools {

Vector3d CanvasToViewport(const Vector2d& pt, const Canvas& canvas, float viewport_size = 1.0)
{
    float x = pt.x() * viewport_size / canvas.width();
    float y = pt.y() * viewport_size / canvas.height();
    return { x, y, viewport_size };
}

double ComputeLighting(const Vector3d& point, const Vector3d& normal, const Vector3d& v, double s, const Scene& scene)
{
    double intensity = 0.0;
    for (int i = 0; i < scene.getLights().size(); i++) {
        auto light = scene.getLights().at(i);
        if (light->getType() == Light::Ambient) {
            intensity += light->getIntensity();
        } else {
            Vector3d vec_l;
            if (light->getType() == Light::Point) {
                auto l = std::static_pointer_cast<PointLight>(light);
                vec_l = l->position() - point;
            } else {
                auto l = std::static_pointer_cast<DirectionalLight>(light);
                vec_l = l->position();
            }
            auto n_dotl = normal.dot(vec_l);
            if (n_dotl > 0) {
                intensity += light->getIntensity() * n_dotl / (normal.norm() * vec_l.norm());
            }

            if (s != -1) {
                Vector3d R = 2 * normal * normal.dot(vec_l);
                double r_dot_v = R.dot(v);
                if (r_dot_v > 0) {
                    intensity += light->getIntensity() * std::pow(r_dot_v / (R.norm() * v.norm()), s);
                }
            }
        }
    }
    return intensity;
}

} // END NAMESPACE

#endif // TOOLS_H
