#include <stdlib.h>
#include <stdio.h>

#include "ray_hit.h"

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
