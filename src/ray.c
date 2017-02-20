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
    char* str;
    char* format = "[(Ray) origin:%s direction:%s]";
    asprintf(&str, format, Vec3ToString(ray->origin), 
            Vec3ToString(ray->direction));
    return str;
}
