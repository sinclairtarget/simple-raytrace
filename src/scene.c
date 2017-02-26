#include <stdlib.h>
#include <stdio.h>

#include "scene.h"

Scene* globalScene;

static void Init();

int SceneAdd(Sphere* sphere)
{
    if (globalScene == NULL)
        Init();

    if (globalScene->objectCount == MAX_SCENE_OBJECTS)
        return 1;

    globalScene->objects[globalScene->objectCount] = sphere;
    (globalScene->objectCount)++;

    return 0;
}

static void Init()
{
    globalScene = (Scene*) calloc(1, sizeof(Scene));
}

char* SceneToString()
{
    char* format = "[(Scene) objectCount:%d]";
    
    char* str;
    asprintf(&str, format, globalScene->objectCount);

    return str;
}
