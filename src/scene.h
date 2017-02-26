#ifndef SCENE_H
#define SCENE_H

#include "surfaces.h"

#define MAX_SCENE_OBJECTS 10

typedef struct {
    Sphere* objects[MAX_SCENE_OBJECTS];
    int objectCount;
} Scene;

extern Scene* globalScene;

// Adds a sphere to the scene.
int SceneAdd(Sphere* sphere);

char* SceneToString();

#endif
