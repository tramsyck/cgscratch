#ifndef CANVAS_H
#define CANVAS_H

#include "scene.h"
#include "viewport.h"

#include <QtGui/QImage>
class Viewport;
class Canvas {
public:
    Canvas(int w, int h, const Viewport& viewport, const Scene& scene);

    int width() const { return _image.width(); }
    int height() const { return _image.height(); }

    const QImage& generate();

    void setCameraPosition(const Vector3d& position);
    /**
     * @brief putPixel set pixel color
     * @param x
     * @param y
     */
    void putPixel(int x, int y, QColor color);

private:
    QImage _image;
    Viewport _viewport;
    Scene _scene;
    Vector3d _cameraPostion;
};

#endif // CANVAS_H
