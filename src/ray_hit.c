#include <stdlib.h>
#include <stdio.h>

#include "ray_hit.h"

char* RayHitToString(RayHit* rayHit)
{
    if (rayHit == NULL)
        return "NULL";

    char* str;
    char* format = "[(RayHit) point:%s normal:%s t:%.2f]";
    asprintf(&str, format, Vec3ToString(rayHit->point),
                           Vec3ToString(rayHit->normal),
                           rayHit->t);
    return str;
}
