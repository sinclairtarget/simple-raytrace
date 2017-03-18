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
} Triangle;

Triangle* TriangleCreate(Vec3 a,
                         Vec3 b,
                         Vec3 c,
                         Color color,
                         Color specularColor,
                         float phongExponent);

// String representation for debugging.
char* TriangleToString(Triangle* triangle);

#endif 
