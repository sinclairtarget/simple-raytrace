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
static void BuildScene();

int main(int argc, char* argv[])
{
    // Initialize the window
    Init();
    RectSize windowSize = CreateWindow(0.8f, 0.8f);
    printf("window: [%.2f, %.2f]\n", windowSize.width, windowSize.height);
    
    // Set up the pixel coordinate array and scramble it
    int totalPixelCount = windowSize.width * windowSize.height;
    OrderedPair coordinateArray[totalPixelCount];
    
    PopulateCoordinateArray(coordinateArray, windowSize);

    // Set up the scene and camera
    Camera* cam = BuildCamera(windowSize);

    BuildScene();

    // Render!
    printf("Rendering...\n");

    int step = 0.1f * totalPixelCount;
    time_t start = time(NULL);

    for (int index = 0; index < totalPixelCount; index++) {
        OrderedPair pixelCoord = coordinateArray[index];

        ProcessEvents();

        int i = pixelCoord.i;
        int j = pixelCoord.j;

        Color pixelColor = CameraSamplePixel(cam, i, j, windowSize);
        SetColor(i, windowSize.height - j, pixelColor); // invert y-axis

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

//    Camera* cam = CameraCreateOrthographic(camPos, upDir, viewDir,
//                                           imagePlaneSize, background);
    Camera* cam = CameraCreatePerspective(camPos, upDir, viewDir,
                                          imagePlaneSize, background,
                                          /* focal length = */ 1.73f);

    dprint(cam, Camera);

    return cam;
}

static void BuildScene()
{
    SceneInit(/* ambient light intensity = */ 0.2f);

    Color specularColor = { 0.6f, 0.6f, 0.6f, 1 };

    Vec3 redSphereCenter = { 1.5f, 0, -2.5f };
    Color red = { 1, 0, 0, 1 };
    Sphere* redSphere = SphereCreate(redSphereCenter, 0.5f, red, 
                                     specularColor, 10);
    SceneAdd(redSphere);

    Vec3 blueSphereCenter = { 0, 0, -3 };
    Color blue = { 0, 0, 1, 1 };
    Sphere* blueSphere = SphereCreate(blueSphereCenter, 0.5f, blue,
                                      specularColor, 100);
    SceneAdd(blueSphere);

    Vec3 greenSphereCenter = { -1.5f, 0, -2.5f };
    Color green = { 0, 1, 0, 1 };
    Sphere* greenSphere = SphereCreate(greenSphereCenter, 0.5f, green,
                                       specularColor, 1000);
    SceneAdd(greenSphere);
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
