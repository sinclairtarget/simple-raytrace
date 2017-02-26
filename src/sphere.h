#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "ray.h"

typedef struct {
    Vec3 center;
    float radius;
    Color color;
} Sphere;

Sphere* SphereCreate(Vec3 center, float radius, Color color);

/* 
 * If the ray intersects the sphere, returns the first intersection (i.e. the
 * intersection closest to the ray's origin).
 * 
 * If the ray does not intersect the sphere, returns nothing.
 */
RayHit* SphereIntersect(Sphere* sphere, Ray* ray);

// String representation for debugging.
char* SphereToString(Sphere* sphere);

#endif
