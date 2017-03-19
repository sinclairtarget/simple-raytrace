#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec3.h"
#include "ray.h"

typedef struct {
    Vec3 a;
    Vec3 b;
    Vec3 c;
    Color color;
    Color specularColor;
    float phongExponent;
    Color reflectiveColor;
} Triangle;

Triangle* TriangleCreate(Vec3 a,
                         Vec3 b,
                         Vec3 c,
                         Color color,
                         Color specularColor,
                         float phongExponent,
                         Color reflectiveColor);

/*
 * Returns the normal vector for the given triangle, in normalized form.
 *
 * The normal points "up" when a, b, and c appear counterclockwise.
 */
Vec3 TriangleNormal(Triangle* triangle);

/* 
 * If the ray intersects the triangle, returns the first intersection (i.e. the
 * intersection closest to the ray's origin).
 * 
 * If the ray does not intersect the triangle, returns nothing.
 */
RayHit* TriangleIntersect(void* surface, Ray* ray);

// String representation for debugging.
char* TriangleToString(Triangle* triangle);

#endif 
