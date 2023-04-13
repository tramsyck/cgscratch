#include "canvas.h"
#include "tools.h"
#include <QDebug>

using namespace tools;
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

Canvas::Canvas(int w, int h, const Viewport& viewport, const Scene& scene)
    : _image(w, h, QImage::Format_RGB32)
    , _viewport(viewport)
    , _scene(scene)
{
}

const QImage& Canvas::generate()
{
    for (int i = -width() / 2; i < width() / 2; ++i) {
        for (int j = -height() / 2; j < height() / 2; ++j) {
            QColor color = Qt::black;
            Vector3d direction = tools::CanvasToViewport(Vector2d { i, j }, *this);
            std::shared_ptr<Sphere> current_sphere = nullptr;
            float closest_t = HUGE_VAL;
            for (auto object : _scene.getSpheres()) {
                auto [t1, t2] = IntersectRaySphere(_cameraPostion, direction, object);

                if (closest_t > t1) {
                    closest_t = t1;
                    current_sphere = object;
                }
                if (closest_t > t2) {
                    closest_t = t2;
                    current_sphere = object;
                }
            }
            if (current_sphere != nullptr) {

                color = current_sphere->color;

                auto point = closest_t * direction;
                Vector3d normal0 = point - current_sphere->center;
                Vector3d normal = (1.0 / normal0.norm()) * normal0;
                auto intensity = tools::ComputeLighting(point, normal, this->_scene);
                color = QColor::fromRgb(std::min<int>(255, color.red() * intensity),
                    std::min<int>(255, color.green() * intensity), std::min<int>(255, color.blue() * intensity));
            } else {
                color = Qt::black;
            }
            putPixel(i, j, color);
        }
    }
    return _image;
}

void Canvas::setCameraPosition(const Vector3d& position)
{
    _cameraPostion = position;
}

void Canvas::putPixel(int x, int y, QColor color)
{
    _image.setPixelColor(x + width() / 2, height() / 2 - y - 1, color);
}
