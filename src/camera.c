#include <stdlib.h>
#include <stdio.h>

#include "camera.h"

Camera* CameraCreate(Vec3 position, Vec3 upDirection, Vec3 viewDirection)
{
    Camera* camera = (Camera*) malloc(sizeof(Camera));
    camera->position = position;
    camera->w = Vec3Neg(Vec3Norm(viewDirection));

    // Construct an orthonormal basis. Start with up x w = u
    Vec3 normalizedUpDirection = Vec3Norm(upDirection);
    camera->u = Vec3Norm(Vec3Cross(normalizedUpDirection, camera->w));

    // Now w x u = v
    camera->v = Vec3Norm(Vec3Cross(camera->w, camera->u));

    return camera;
}

char* CameraToString(Camera* camera)
{
    char* format = "[(Camera) position:%s u:%s v:%s w:%s]";

    char* position = Vec3ToString(camera->position);
    char* u = Vec3ToString(camera->u);
    char* v = Vec3ToString(camera->v);
    char* w = Vec3ToString(camera->w);

    char* str;
    asprintf(&str, format, position, u, v, w);

    free(position);
    free(u);
    free(v);
    free(w);

    return str;
}
