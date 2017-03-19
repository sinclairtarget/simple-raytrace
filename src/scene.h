#ifndef SCENE_H
#define SCENE_H

#include "surfaces.h"

#define MAX_SCENE_OBJECTS 10

typedef RayHit* (*IntersectFunction)(void* surface, Ray* ray);

typedef struct {
    void* surface;
    IntersectFunction intersectFunction;
} SceneObject;

typedef struct {
    SceneObject* objects[MAX_SCENE_OBJECTS];
    int objectCount;
    Vec3 lightDirection;
    float ambientLightIntensity;
} Scene;

extern Scene* globalScene;

void SceneInit(Vec3 lightDirection, float ambientLightIntensity);

// Adds a sphere to the scene.
int SceneAddSphere(Sphere* sphere);

// Adds a triangle to the scene.
int SceneAddTriangle(Triangle* triangle);

// Returns the intersect between the ray and the given scene object, or NULL if
// no intersection exists.
RayHit* SceneObjectIntersect(SceneObject* obj, Ray* ray);

char* SceneToString();

#endif
