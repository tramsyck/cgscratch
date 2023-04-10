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

} // END NAMESPACE

#endif // TOOLS_H
