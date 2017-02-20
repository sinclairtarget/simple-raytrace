#ifndef RAY_HIT_H
#define RAY_HIT_H

#include "vec3.h"

// Describes an intersection between a ray and a surface.
typedef struct {
    Vec3 point;  // The world-space point at which the intersection occurred.
    Vec3 normal; // The normal vector on the surface at the intersection point.
    float t;     // The ray parameter. (How far along the ray?)
} RayHit;

// String representation for debugging.
char* RayHitToString(RayHit* rayHit);

#endif
