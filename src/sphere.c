#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "sphere.h"

Sphere* SphereCreate(Vec3 center, float radius)
{
    Sphere* sphere = (Sphere*) malloc(sizeof(Sphere));
    sphere->center = center;
    sphere->radius = radius;
    return sphere;
}

RayHit* SphereIntersect(Sphere* sphere, Ray* ray)
{
    Vec3 originMinusCenter = Vec3Sub(ray->origin, sphere->center);
    float dotDirection = Vec3Dot(ray->direction, ray->direction);

    // descriminant = (b^2) - a c
    float b = Vec3Dot(ray->direction, originMinusCenter);
    float a = Vec3Dot(ray->direction, ray->direction);
    float c = Vec3Dot(originMinusCenter, originMinusCenter) - 
        sphere->radius * sphere->radius;

    float desc = b * b - a * c;
    if (desc < 0) // No intersection
        return NULL;

    // solve quadratic equation
    float outsideSqrt = Vec3Dot(Vec3Neg(ray->direction), originMinusCenter);
    float t1 = (outsideSqrt - sqrt(desc)) / dotDirection;
    float t2 = (outsideSqrt + sqrt(desc)) / dotDirection;

    float smallerT = t1 < t2 ? t1 : t2;

    RayHit* hit = calloc(1, sizeof(RayHit));
    hit->point = RayEvaluatePoint(ray, smallerT);
    hit->t = smallerT;
    return hit;
}

char* SphereToString(Sphere* sphere)
{
    char* str;
    char* format = "[(Sphere) center:%s radius:%.2f]";
    asprintf(&str, format, Vec3ToString(sphere->center), sphere->radius);
    return str;
}
