#include <stdio.h>
#include <stdlib.h>

#include "sphere.h"

Sphere* SphereCreate(Vec3 center, float radius)
{
    Sphere* sphere = (Sphere*) malloc(sizeof(Sphere));
    sphere->center = center;
    sphere->radius = radius;
    return sphere;
}

char* SphereToString(Sphere* sphere)
{
    char* str;
    char* format = "[(Sphere) center:%s radius:%.2f]";
    asprintf(&str, format, Vec3ToString(sphere->center), sphere->radius);
    return str;
}
