#include <stdlib.h>
#include <stdio.h>

#include "scene.h"

Scene* globalScene;

void SceneInit(float ambientLightIntensity)
{
    globalScene = (Scene*) calloc(1, sizeof(Scene));
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
