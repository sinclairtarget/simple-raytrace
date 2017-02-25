#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

typedef struct {
    Vec3 position;
    Vec3 u; // rightward in relation the the view direction
    Vec3 v; // upward in relation to the view direction
    Vec3 w; // opposite the view direction, out the back of the camera
} Camera;

Camera* CameraCreate(Vec3 position, Vec3 upDirection, Vec3 viewDirection);

// String representation for debugging.
char* CameraToString(Camera* camera);

#endif
