#include <stdlib.h>
#include <stdio.h>

#include "scene.h"

Scene* globalScene;

void SceneInit(Vec3 lightDirection, float ambientLightIntensity)
{
    globalScene = (Scene*) calloc(1, sizeof(Scene));
    globalScene->lightDirection = lightDirection;
    globalScene->ambientLightIntensity = ambientLightIntensity;
}

int SceneAddSphere(Sphere* sphere)
{
    if (globalScene == NULL)
        return 1;

    if (globalScene->objectCount == MAX_SCENE_OBJECTS)
        return 2;

    SceneObject* obj = malloc(sizeof(SceneObject));
    obj->surface = sphere;
    obj->intersectFunction = SphereIntersect;

    globalScene->objects[globalScene->objectCount] = obj;
    (globalScene->objectCount)++;

    return 0;
}

int SceneAddTriangle(Triangle* triangle)
{
    if (globalScene == NULL)
        return 1;

    if (globalScene->objectCount == MAX_SCENE_OBJECTS)
        return 2;

    SceneObject* obj = malloc(sizeof(SceneObject));
    obj->surface = triangle;
    obj->intersectFunction = TriangleIntersect;

    globalScene->objects[globalScene->objectCount] = obj;
    (globalScene->objectCount)++;

    return 0;
}

RayHit* SceneObjectIntersect(SceneObject* obj, Ray* ray)
{
    return obj->intersectFunction(obj->surface, ray);
}

char* SceneToString()
{
    if (globalScene == NULL)
        return "NULL";

    char* format = "[(Scene) objectCount:%d]";
    
    char* str;
    asprintf(&str, format, globalScene->objectCount);

    return str;
}
