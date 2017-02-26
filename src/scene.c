#include <stdlib.h>
#include <stdio.h>

#include "scene.h"

Scene* globalScene;

void SceneInit(float ambientLightIntensity)
{
    globalScene = (Scene*) calloc(1, sizeof(Scene));
    globalScene->ambientLightIntensity = ambientLightIntensity;
}

int SceneAdd(Sphere* sphere)
{
    if (globalScene == NULL)
        return 1;

    if (globalScene->objectCount == MAX_SCENE_OBJECTS)
        return 2;

    globalScene->objects[globalScene->objectCount] = sphere;
    (globalScene->objectCount)++;

    return 0;
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
