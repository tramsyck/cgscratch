#include "canvas.h"
#include "tools.h"
#include <QDebug>

using namespace tools;
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
            std::shared_ptr<Sphere> current_sphere = nullptr;
            float closest_t = HUGE_VAL;
            for (auto object : _scene.getSpheres()) {
                float a = (tools::CanvasToViewport(Vector2d { i, j }, *this) - _cameraPostion).dot(tools::CanvasToViewport(Vector2d { i, j }, *this) - _cameraPostion);

                float b = 2 * ((tools::CanvasToViewport(Vector2d { i, j }, *this)).dot(_cameraPostion - object->center));
                float c = (_cameraPostion - object->center).dot(_cameraPostion - object->center) - object->radius * object->radius;
                float descriminant = b * b - 4 * a * c;

                if (descriminant < 0) {
                    continue;
                } else {

                    float t1 = (-b + std::sqrt(descriminant)) / (2 * a);
                    float t2 = (-b - std::sqrt(descriminant)) / (2 * a);

                    if (closest_t > t1) {
                        closest_t = t1;
                        current_sphere = object;
                    }
                    if (closest_t > t2) {
                        closest_t = t2;
                        current_sphere = object;
                    }
                    color = current_sphere->color;
                }
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
