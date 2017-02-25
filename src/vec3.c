#include <stdio.h>
#include <math.h>

#include "Vec3.h"

Vec3 Vec3Neg(Vec3 v)
{
    v.x = -v.x;
    v.y = -v.y;
    v.z = -v.z;
    return v;
}

Vec3 Vec3Norm(Vec3 v)
{
    float scalar = 1 / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    return Vec3Scale(v, scalar);
}

Vec3 Vec3Add(Vec3 a, Vec3 b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

Vec3 Vec3Sub(Vec3 a, Vec3 b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

Vec3 Vec3Scale(Vec3 v, float scalar)
{
    v.x *= scalar;
    v.y *= scalar;
    v.z *= scalar;
    return v;
}

float Vec3Dot(Vec3 a, Vec3 b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    return a.x + a.y + a.z;
}

Vec3 Vec3Cross(Vec3 a, Vec3 b)
{
    Vec3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

char* Vec3ToString(Vec3 v)
{
    char* str;
    asprintf(&str, "[(Vec3) <%.2f, %.2f, %.2f>]", v.x, v.y, v.z);
    return str;
}
