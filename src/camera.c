#include <stdlib.h>
#include <stdio.h>

#include "camera.h"
#include "ray.h"
#include "sphere.h"
#include "scene.h"

static Ray* CameraGenerateRayOrthographic(Camera* camera, 
                                          int i, 
                                          int j, 
                                          RectSize imageSize);

static Ray* CameraGenerateRayPerspective(Camera* camera, 
                                         int i, 
                                         int j, 
                                         RectSize imageSize);

Camera* CameraCreateOrthographic(Vec3 position, 
                                 Vec3 upDirection, 
                                 Vec3 viewDirection,
                                 RectSize imagePlaneSize)
{
    Camera* camera = (Camera*) malloc(sizeof(Camera));

    camera->position = position;
    camera->w = Vec3Neg(Vec3Norm(viewDirection));

    // Construct an orthonormal basis. Start with up x w = u
    Vec3 normalizedUpDirection = Vec3Norm(upDirection);
    camera->u = Vec3Norm(Vec3Cross(normalizedUpDirection, camera->w));

    // Now w x u = v
    camera->v = Vec3Norm(Vec3Cross(camera->w, camera->u));

    camera->mode = ORTHOGRAPHIC;
    camera->imagePlaneSize = imagePlaneSize;

    return camera;
}

RayHit* CameraSamplePixel(Camera* camera, int i, int j, RectSize imageSize)
{
    Ray* ray;
    if (camera->mode == ORTHOGRAPHIC)
        ray = CameraGenerateRayOrthographic(camera, i, j, imageSize);
    else
        ray = CameraGenerateRayPerspective(camera, i, j, imageSize);

    RayHit* closestHit = NULL;
    for (int index = 0; index < globalScene->objectCount; index++) {
        Sphere* sphere = globalScene->objects[index];
        RayHit* hit = SphereIntersect(sphere, ray);

        if (hit == NULL)
            continue;

        if (closestHit == NULL || hit->t < closestHit->t)
            closestHit = hit;
    }

    return closestHit;
}

char* CameraToString(Camera* camera)
{
    char* format = "[(Camera) position:%s u:%s v:%s w:%s width:%d height:%d]";

    char* position = Vec3ToString(camera->position);
    char* u = Vec3ToString(camera->u);
    char* v = Vec3ToString(camera->v);
    char* w = Vec3ToString(camera->w);

    char* str;
    asprintf(&str, format, position, u, v, w, camera->imagePlaneSize.width,
             camera->imagePlaneSize.height);

    free(position);
    free(u);
    free(v);
    free(w);

    return str;
}

static Ray* CameraGenerateRayOrthographic(Camera* camera,
                                          int i,
                                          int j,
                                          RectSize imageSize)
{
    // Start the ray at the appropriate position on the image plane
    float planeWidth = camera->imagePlaneSize.width;
    float planeHeight = camera->imagePlaneSize.height;
    float imageWidth = imageSize.width;
    float imageHeight = imageSize.height;

    float leftEdge = -(planeWidth / 2.f);
    float bottomEdge = -(planeHeight / 2.f);

    float uScalar = leftEdge + (i + 0.5f) * (planeWidth / imageWidth);
    float vScalar = bottomEdge + (j + 0.5f) * (planeHeight / imageHeight);

    Vec3 pixelU = Vec3Scale(camera->u, uScalar);
    Vec3 pixelV = Vec3Scale(camera->v, vScalar);

    Vec3 origin = Vec3Add(camera->position, Vec3Add(pixelU, pixelV));

    // Orthographic, so all rays go in the view direction
    return RayCreate(origin, Vec3Neg(camera->w));
}

static Ray* CameraGenerateRayPerspective(Camera* camera,
                                         int i,
                                         int j,
                                         RectSize imageSize)
{
    return NULL;
}
