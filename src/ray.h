#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;

// Describes an intersection between a ray and a surface.
typedef struct {
    Vec3 point;  // The world-space point at which the intersection occurred.
    Vec3 normal; // The normal vector on the surface at the intersection point.
    float t;     // The ray parameter. (How far along the ray?)
} RayHit;

Ray* RayCreate(Vec3 origin, Vec3 direction);

// Returns the point along the ray where the ray parameter is t.
Vec3 RayEvaluatePoint(Ray* ray, float t);

// String representation for debugging.
char* RayToString(Ray* ray);

#endif
