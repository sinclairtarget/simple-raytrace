#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "ray_hit.h"

typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;

Ray* RayCreate(Vec3 origin, Vec3 direction);

// Returns the point along the ray where the ray parameter is t.
Vec3 RayEvaluatePoint(Ray* ray, float t);

// String representation for debugging.
char* RayToString(Ray* ray);

#endif
