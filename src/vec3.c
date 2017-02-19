#include <stdio.h>

#include "Vec3.h"

Vec3 Vec3Add(Vec3 a, Vec3 b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

float Vec3Dot(Vec3 a, Vec3 b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    return a.x + a.y + a.z;
}

char* Vec3ToString(Vec3 v)
{
    char* str;
    asprintf(&str, "[(Vec3) <%.2f, %.2f, %.2f>]", v.x, v.y, v.z);
    return str;
}
