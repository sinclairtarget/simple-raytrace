#ifndef SHADING_H
#define SHADING_H

#include "camera.h"
#include "ray.h"

Color Shade(Camera* camera, RayHit* hit);

#endif
