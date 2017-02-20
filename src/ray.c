#include <stdlib.h>
#include <stdio.h>

#include "ray.h"

Ray* RayCreate(Vec3 origin, Vec3 direction)
{
    Ray* ray = malloc(sizeof(Ray));
    ray->origin = origin;
    ray->direction = direction;
    return ray;
}

Vec3 RayEvaluatePoint(Ray* ray, float t)
{
    return Vec3Add(ray->origin, Vec3Scale(ray->direction, t));
}

char* RayToString(Ray* ray)
{
    char* format = "[(Ray) origin:%s direction:%s]";

    char* origin = Vec3ToString(ray->origin);
    char* direction = Vec3ToString(ray->direction);

    char* str;
    asprintf(&str, format, origin, direction);

    free(origin);
    free(direction);

    return str;
}
