#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "platform.h"
#include "ray.h"
#include "camera.h"
#include "scene.h"
#include "macros.h"
#include "random_sort.h"

static Camera* BuildCamera();
static void PopulateCoordinateArray(OrderedPair array[], RectSize windowSize);

int main(int argc, char* argv[])
{
    // Initialize the window
    Init();
    RectSize windowSize = CreateWindow(0.8f, 0.8f);
    
    // Set up the pixel coordinate array and scramble it
    int totalPixelCount = windowSize.width * windowSize.height;
    OrderedPair coordinateArray[totalPixelCount];
    
    PopulateCoordinateArray(coordinateArray, windowSize);

    // Set up the scene and camera
    Camera* cam = BuildCamera(windowSize);

    SceneInit(0.2f);

    Vec3 blueSphereCenter = { -1, 0, -5 };
    Color blue = { 0, 0, 1, 1 };
    Sphere* blueSphere = SphereCreate(blueSphereCenter, 0.5f, blue);
    SceneAdd(blueSphere);

    Vec3 greenSphereCenter = { 1, 0, -7 };
    Color green = { 0, 1, 0, 1 };
    Sphere* greenSphere = SphereCreate(greenSphereCenter, 0.5f, green);
    SceneAdd(greenSphere);

    // Render!
    printf("Rendering...\n");
    time_t start = time(NULL);

    for (int index = 0; index < totalPixelCount; index++) {
        OrderedPair pixelCoord = coordinateArray[index];

        ProcessEvents();

        int i = pixelCoord.i;
        int j = pixelCoord.j;

        Color pixelColor = CameraSamplePixel(cam, i, j, windowSize);
        SetColor(i, windowSize.height - j, pixelColor); // invert y-axis

        int step = 0.1f * totalPixelCount;
        if (index % step == 0) {
            ProcessEvents();
            Draw();
        }
    }

    Draw();
    time_t finish = time(NULL);
    time_t elapsed = finish - start;
    printf("Done! Finished in %ld seconds.\n", elapsed);

    while (1) {
        ProcessEvents();
        usleep((1.0f/30) * 1000000);
    }

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

    return cam;
}

static void PopulateCoordinateArray(OrderedPair array[], RectSize windowSize)
{
    for (int i = 0; i < windowSize.width; i++) {
        for (int j = 0; j < windowSize.height; j++) {
            int index = j + i * windowSize.height;
            array[index].i = i;
            array[index].j = j;
        }
    }

    int totalPixelCount = windowSize.width * windowSize.height;
    RandomSort(array, totalPixelCount);
}
