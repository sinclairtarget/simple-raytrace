#include <stdio.h>
#include <stdlib.h>

#include "triangle.h"

Triangle* TriangleCreate(Vec3 a,
                         Vec3 b,
                         Vec3 c,
                         Color color,
                         Color specularColor,
                         float phongExponent,
                         Color reflectiveColor)
{
    Triangle* triangle = (Triangle*) malloc(sizeof(Triangle));

    triangle->a = a;
    triangle->b = b;
    triangle->c = c;
    triangle->color = color;
    triangle->specularColor = specularColor;
    triangle->phongExponent = phongExponent;
    triangle->reflectiveColor = reflectiveColor;

    return triangle;
}

Vec3 TriangleNormal(Triangle* triangle)
{
    Vec3 ab = Vec3Sub(triangle->b, triangle->a);
    Vec3 ac = Vec3Sub(triangle->c, triangle->a);
    return Vec3Norm(Vec3Cross(ab, ac));
}

RayHit* TriangleIntersect(void* surface, Ray* ray)
{
    Triangle* tri = (Triangle*) surface;

    // Solve linear system using cramer's rule to find intersection between
    // ray and triangle defined in barycentric form.
    float a = tri->a.x - tri->b.x;
    float b = tri->a.y - tri->b.y;
    float c = tri->a.z - tri->b.z;
    float d = tri->a.x - tri->c.x;
    float e = tri->a.y - tri->c.y;
    float f = tri->a.z - tri->c.z;
    float g = ray->direction.x;
    float h = ray->direction.y;
    float i = ray->direction.z;

    float j = tri->a.x - ray->origin.x;
    float k = tri->a.y - ray->origin.y;
    float l = tri->a.z - ray->origin.z;

    float eihf = e * i - h * f;
    float gfdi = g * f - d * i;
    float dheg = d * h - e * g;

    float M = a * eihf + b * gfdi + c * dheg;

    float akjb = a * k - j * b;
    float jcal = j * c - a * l;
    float blkc = b * l - k * c;

    float t = -(f * akjb + e * jcal + d * blkc) / M;
    if (t < 0)
        return NULL;

    float gamma = (i * akjb + h * jcal + g * blkc) / M;
    if (gamma < 0 || gamma > 1)
        return NULL;

    float beta = (j * eihf + k * gfdi + l * dheg) / M;
    if (beta < 0 || beta > 1 - gamma)
        return NULL;

    Vec3 point = RayEvaluatePoint(ray, t);
    Vec3 normal = TriangleNormal(tri);

    RayHit* hit = RayHitCreate(tri->color, tri->specularColor,
                               tri->phongExponent, tri->reflectiveColor,
                               point, normal, t);
    return hit;
}

char* TriangleToString(Triangle* triangle)
{
    char* format = "[(Triangle) a:%s b%s c:%s]";

    char* a = Vec3ToString(triangle->a);
    char* b = Vec3ToString(triangle->b);
    char* c = Vec3ToString(triangle->c);

    char* str;
    asprintf(&str, format, a, b, c);

    free(a);
    free(b);
    free(c);

    return str;
}
