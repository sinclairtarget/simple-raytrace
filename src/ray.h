#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;

Ray* RayCreate(Vec3 origin, Vec3 direction);

// String representation for debugging.
char* RayToString(Ray* ray);

#endif
