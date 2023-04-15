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
std::tuple<double, double> IntersectRaySphere(Vector3d origin, Vector3d direction, std::shared_ptr<Sphere> sphere)
{
    Vector3d oc = origin - sphere->center;
    float a = direction.dot(direction);

    float b = 2 * oc.dot(direction);
    float c = oc.dot(oc) - sphere->radius * sphere->radius;
    float descriminant = b * b - 4 * a * c;

    if (descriminant < 0) {
        return { INFINITY, INFINITY };
    }

    float t1 = (-b + std::sqrt(descriminant)) / (2 * a);
    float t2 = (-b - std::sqrt(descriminant)) / (2 * a);
    return { t1, t2 };
}
std::tuple<std::shared_ptr<Sphere>, double> ClosestIntersection(const Vector3d& origin, const Vector3d& direction, double t_min, double t_max, const Scene& scene)
{
    std::shared_ptr<Sphere> current_sphere = nullptr;
    float closest_t = HUGE_VAL;
    for (auto object : scene.getSpheres()) {
        auto [t1, t2] = IntersectRaySphere(origin, direction, object);

        if (closest_t > t1 && t_min < t1 && t1 < t_max) {
            closest_t = t1;
            current_sphere = object;
        }
        if (closest_t > t2 && t_min < t2 && t2 < t_max) {
            closest_t = t2;
            current_sphere = object;
        }
    }
    return { current_sphere, closest_t };
}

double ComputeLighting(const Vector3d& point, const Vector3d& normal, const Vector3d& v, double s, const Scene& scene)
{
    double intensity = 0.0;
    double t_max = 0;
    for (int i = 0; i < scene.getLights().size(); i++) {
        auto light = scene.getLights().at(i);
        if (light->getType() == Light::Ambient) {
            intensity += light->getIntensity();
        } else {
            Vector3d vec_l;
            if (light->getType() == Light::Point) {
                auto l = std::static_pointer_cast<PointLight>(light);
                vec_l = l->position() - point;
                t_max = 1;
            } else {
                auto l = std::static_pointer_cast<DirectionalLight>(light);
                vec_l = l->position();
                t_max = INFINITY;
            }
            auto [sphere, shadow_t] = ClosestIntersection(point, vec_l, 0.001, t_max, scene);
            if (sphere != nullptr)
                continue;
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
