#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "platform.h"
#include "ray.h"
#include "camera.h"
#include "scene.h"

int main(int argc, char* argv[])
{
    Init();
    RectSize windowSize = CreateWindow(0.8f, 0.8f);

    Vec3 camPos = { 0, 0, 0 };
    Vec3 upDir = { 0, 1, 0 };
    Vec3 viewDir = { 0, 0, -1 }; 

    float aspect = windowSize.width / (float)windowSize.height;
    RectSize imagePlaneSize = { 2 * aspect, 2 };
    Camera* cam = CameraCreateOrthographic(camPos, upDir, viewDir, 
                                           imagePlaneSize);

    printf("cam: %s\n", CameraToString(cam));

    Vec3 center = { 0, 0, -5 };
    Sphere* sphere = SphereCreate(center, 0.5f);
    SceneAdd(sphere);

    printf("scene: %s\n", SceneToString());

    Color red = { 1, 0, 0, 1 };
    Color blue = { 0, 1, 0, 1 };

    int x = 0;
    int y = 0;

    for (;;) {
        ProcessEvents();

        if (y < windowSize.height) {
            int i = x;
            int j = windowSize.height - y;
            RayHit* hit = CameraSamplePixel(cam, i, j, windowSize);
            
            if (hit == NULL)
                Draw(x, y, blue);
            else
                Draw(x, y, red);

            free(hit);

            x += 1;

            if (x == windowSize.width) {
                x = 0;
                y += 1;
            }
        }
    }

//    init();
//    RectSize size = createWindow(0.8f, 0.8f);
//
//    Color red = { 1, 0, 0, 1 };
//
//    int x = 0;
//    int y = 0;
//
//    for (;;) {
//        processEvents();
//
//        if (x < size.width && y < size.height) {
//            draw(x, y, red);
//            x += 1;
//            y += 1;
//        }
//        
//        usleep((1.0f/60) * 1000000);
//    }

    return 0;
}
