#include "canvas.h"
#include "tools.h"
#include <QDebug>

using namespace tools;

QColor TraceRay(const Vector3d& origin, const Vector3d& direction, double min_t, double max_t, const Scene& scene)
{
    QColor color = Qt::black;

    auto [closest_sphere, closest_t] = tools::ClosestIntersection(origin, direction, min_t, max_t, scene);
    if (closest_sphere != nullptr) {

        color = closest_sphere->color;

        auto point = closest_t * direction;
        Vector3d normal0 = point - closest_sphere->center;
        Vector3d normal = (1.0 / normal0.norm()) * normal0;
        auto intensity = tools::ComputeLighting(point, normal, -direction, closest_sphere->specular, scene);
        color = QColor::fromRgb(std::min<int>(255, color.red() * intensity),
            std::min<int>(255, color.green() * intensity), std::min<int>(255, color.blue() * intensity));
        return color;
    }
    return color;
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
            Vector3d direction = tools::CanvasToViewport(Vector2d { i, j }, *this);
            auto color = TraceRay(_cameraPostion, direction, 1, INFINITY, this->_scene);
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
