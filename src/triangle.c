#include <stdio.h>
#include <stdlib.h>

#include "triangle.h"

Triangle* TriangleCreate(Vec3 a,
                         Vec3 b,
                         Vec3 c,
                         Color color,
                         Color specularColor,
                         float phongExponent)
{
    Triangle* triangle = (Triangle*) malloc(sizeof(Triangle));

    triangle->a = a;
    triangle->b = b;
    triangle->c = c;
    triangle->color = color;
    triangle->specularColor = specularColor;
    triangle->phongExponent = phongExponent;

    return triangle;
}

char* TriangleToString(Triangle* triangle)
{
    char* format = "[(Triangle) a:%s b%a c:%a]";

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
