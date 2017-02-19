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

char* RayToString(Ray* ray)
{
    char* str;
    char* format = "[(Ray) origin:%s direction:%s]";
    asprintf(&str, format, Vec3ToString(ray->origin), 
            Vec3ToString(ray->direction));
    return str;
}
