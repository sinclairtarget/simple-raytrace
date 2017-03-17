#include <stdlib.h>
#include <stdio.h>

#include "camera.h"
#include "ray.h"
#include "shading.h"
#include "macros.h"

static Camera* CameraCreate(Vec3 position, 
                            Vec3 upDirection, 
                            Vec3 viewDirection,
                            RectSize imagePlaneSize,
                            Color backgroundColor,
                            CameraMode mode,
                            float focalLength);

static Ray* CameraGenerateRayOrthographic(Camera* camera, 
                                          int i, 
                                          int j, 
                                          RectSize imageSize);

static Ray* CameraGenerateRayPerspective(Camera* camera, 
                                         int i, 
                                         int j, 
                                         RectSize imageSize);

static void FillPixelVectorCoordinates(Camera* camera, 
                                       Vec3* pixelU, 
                                       Vec3* pixelV,
                                       int i, 
                                       int j,
                                       RectSize imageSize);

Camera* CameraCreateOrthographic(Vec3 position,
                                 Vec3 upDirection, 
                                 Vec3 viewDirection,
                                 RectSize imagePlaneSize,
                                 Color backgroundColor)
{
    return CameraCreate(position, upDirection, viewDirection, imagePlaneSize,
                        backgroundColor, ORTHOGRAPHIC, 0);
}

Camera* CameraCreatePerspective(Vec3 position,
                                Vec3 upDirection, 
                                Vec3 viewDirection,
                                RectSize imagePlaneSize,
                                Color backgroundColor,
                                float focalLength)
{
    return CameraCreate(position, upDirection, viewDirection, imagePlaneSize,
                        backgroundColor, PERSPECTIVE, focalLength);
}

Color CameraSamplePixel(Camera* camera, int i, int j, RectSize imageSize)
{
    Ray* ray;
    if (camera->mode == ORTHOGRAPHIC)
        ray = CameraGenerateRayOrthographic(camera, i, j, imageSize);
    else
        ray = CameraGenerateRayPerspective(camera, i, j, imageSize);

    RayHit* hit = RayCast(ray);

    Color color;
    if (hit == NULL)
        color = camera->backgroundColor;
    else
        color = Shade(camera, hit);

    free(ray);
    free(hit);

    return color;
}

char* CameraToString(Camera* camera)
{
    char* format = 
        "[(Camera) position:%s u:%s v:%s w:%s width:%.2f height:%.2f" \
            " focal length:%.2f]";

    char* position = Vec3ToString(camera->position);
    char* u = Vec3ToString(camera->u);
    char* v = Vec3ToString(camera->v);
    char* w = Vec3ToString(camera->w);

    char* str;
    asprintf(&str, format, position, u, v, w, camera->imagePlaneSize.width,
             camera->imagePlaneSize.height, camera->focalLength);

    free(position);
    free(u);
    free(v);
    free(w);

    return str;
}

static Camera* CameraCreate(Vec3 position, 
                            Vec3 upDirection, 
                            Vec3 viewDirection,
                            RectSize imagePlaneSize,
                            Color backgroundColor,
                            CameraMode mode,
                            float focalLength)
{
    Camera* camera = (Camera*) malloc(sizeof(Camera));

    camera->position = position;
    camera->w = Vec3Neg(Vec3Norm(viewDirection));

    // Construct an orthonormal basis. Start with up x w = u
    Vec3 normalizedUpDirection = Vec3Norm(upDirection);
    camera->u = Vec3Norm(Vec3Cross(normalizedUpDirection, camera->w));

    // Now w x u = v
    camera->v = Vec3Norm(Vec3Cross(camera->w, camera->u));

    camera->mode = mode;
    camera->imagePlaneSize = imagePlaneSize;
    camera->backgroundColor = backgroundColor;
    camera->focalLength = focalLength;

    return camera;
}

static Ray* CameraGenerateRayOrthographic(Camera* camera,
                                          int i,
                                          int j,
                                          RectSize imageSize)
{
    // Start the ray at the appropriate position on the image plane
    Vec3 pixelU, pixelV;
    FillPixelVectorCoordinates(camera, &pixelU, &pixelV, i, j, imageSize);

    Vec3 origin = Vec3Add(camera->position, Vec3Add(pixelU, pixelV));

    // Orthographic, so all rays go in the view direction
    return RayCreate(origin, Vec3Neg(camera->w)); // 2nd arg will be normalized
}

static Ray* CameraGenerateRayPerspective(Camera* camera,
                                         int i,
                                         int j,
                                         RectSize imageSize)
{
    // u, v components of ray direction
    Vec3 pixelU, pixelV;
    FillPixelVectorCoordinates(camera, &pixelU, &pixelV, i, j, imageSize);

    // w component of ray direction
    Vec3 wDir = Vec3Scale(Vec3Neg(camera->w), camera->focalLength);

    // Add all components together
    Vec3 dir = Vec3Add(Vec3Add(pixelU, pixelV), wDir);

    // Perspective, so all rays start from the camera
    return RayCreate(camera->position, dir); // dir will be normalized
}

/* 
 * Fills the passed arguments with the 2D vector coordinates of the pixel on
 * the image plane.
 */
static void FillPixelVectorCoordinates(Camera* camera, 
                                       Vec3* pixelU, 
                                       Vec3* pixelV,
                                       int i, 
                                       int j,
                                       RectSize imageSize)
{
    float planeWidth = camera->imagePlaneSize.width;
    float planeHeight = camera->imagePlaneSize.height;
    float imageWidth = imageSize.width;
    float imageHeight = imageSize.height;

    float leftEdge = -(planeWidth / 2.f);
    float bottomEdge = -(planeHeight / 2.f);

    float uScalar = leftEdge + (i + 0.5f) * (planeWidth / imageWidth);
    float vScalar = bottomEdge + (j + 0.5f) * (planeHeight / imageHeight);

    *pixelU = Vec3Scale(camera->u, uScalar);
    *pixelV = Vec3Scale(camera->v, vScalar);
}
