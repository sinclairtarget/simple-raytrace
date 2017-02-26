#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "platform.h"
#include "ray.h"
#include "camera.h"
#include "scene.h"
#include "macros.h"

static Camera* BuildCamera();

int main(int argc, char* argv[])
{
    Init();
    RectSize windowSize = CreateWindow(0.8f, 0.8f);

    Camera* cam = BuildCamera(windowSize);
    SceneInit(0.2f);

    Vec3 center = { 0, 0, -5 };
    Color blue = { 0, 0, 1, 1 };
    Sphere* sphere = SphereCreate(center, 0.5f, blue);
    SceneAdd(sphere);

    int x = 0;
    int y = 0;

    for (;;) {
        ProcessEvents();

        if (y < windowSize.height) {
            int i = x;
            int j = windowSize.height - y;
            
            Color pixelColor = CameraSamplePixel(cam, i, j, windowSize);
            SetColor(x, y, pixelColor);

            x += 1;

            if (x == windowSize.width) {
                x = 0;
                y += 1;
                Draw();
            }
        }
    }

//        usleep((1.0f/60) * 1000000);

    return 0;
}

static Camera* BuildCamera(RectSize windowSize)
{
    Vec3 camPos = { 0, 0, 0 };
    Vec3 upDir = { 0, 1, 0 };
    Vec3 viewDir = { 0, 0, -1 }; 

    float aspect = windowSize.width / (float)windowSize.height;
    RectSize imagePlaneSize = { 2 * aspect, 2 };

    Color background = { 0, 0, 0, 1 };

    Camera* cam = CameraCreateOrthographic(camPos, upDir, viewDir, 
                                           imagePlaneSize, background);

    dprint(cam, Camera);

    return cam;
}
