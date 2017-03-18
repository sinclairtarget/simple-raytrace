#include <stdlib.h>
#include <stdio.h>

#include "ray_hit.h"

RayHit* RayHitCreate(Color surfaceColor, 
                     Color surfaceSpecularColor,
                     float surfacePhongExponent,
                     Vec3 point, 
                     Vec3 normal, 
                     float t)
{
    RayHit* hit = (RayHit*) malloc(sizeof(RayHit));

    hit->surfaceColor = surfaceColor;
    hit->surfaceSpecularColor = surfaceSpecularColor;
    hit->surfacePhongExponent = surfacePhongExponent;
    hit->point = point;
    hit->normal = normal;
    hit->t = t;

    return hit;
}

char* RayHitToString(RayHit* rayHit)
{
    if (rayHit == NULL)
        return "NULL";

    char* format = "[(RayHit) point:%s normal:%s t:%.2f]";

    char* point = Vec3ToString(rayHit->point);
    char* normal = Vec3ToString(rayHit->normal);

    char* str;
    asprintf(&str, format, point, normal, rayHit->t);

    free(point);
    free(normal);

    return str;
}
