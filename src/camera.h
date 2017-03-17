#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "graphics.h"

typedef enum { ORTHOGRAPHIC, PERSPECTIVE } CameraMode;

typedef struct {
    Vec3 position;
    Vec3 u; // rightward in relation the the view direction
    Vec3 v; // upward in relation to the view direction
    Vec3 w; // opposite the view direction, out the back of the camera
    CameraMode mode;
    RectSize imagePlaneSize;
    Color backgroundColor;
    float focalLength; // ONLY USED BY PERSPECTIVE CAMERAS
} Camera;

Camera* CameraCreateOrthographic(Vec3 position,
                                 Vec3 upDirection, 
                                 Vec3 viewDirection,
                                 RectSize imagePlaneSize,
                                 Color backgroundColor);

Camera* CameraCreatePerspective(Vec3 position,
                                Vec3 upDirection, 
                                Vec3 viewDirection,
                                RectSize imagePlaneSize,
                                Color backgroundColor,
                                float focalLength);

/*
 * Takes a color sample of the scene to be shown at pixel i, j of a final
 * image.
 *
 * (i: 0, j: 0) is the bottom left of the image.
 */
Color CameraSamplePixel(Camera* camera, int i, int j, RectSize imageSize);

// String representation for debugging.
char* CameraToString(Camera* camera);

#endif
