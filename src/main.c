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
    Vec3 camPos = { 0, 1.2f, 0 };
    Vec3 upDir = { 0, 1, 0 };
    Vec3 viewDir = { 0, -0.5f, -1 }; 

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

    Color floorColor = { 0.4f, 0.4f, 0.33f, 1 };
    Color gray = { 0.6f, 0.6f, 0.6f, 1 };
    Color red = { 0.71f, 0.25f, 0.25f, 1 };
    Color blue = { 0.31f, 0.52f, 0.85f, 1 };
    Color green = { 0.33f, 0.71f, 0.31f, 1 };

    // Create a floor from two tris
    Vec3 a = { -2.5f, -0.5f, 0 };
    Vec3 b = { 2.5f, -0.5f, 0 };
    Vec3 c = { -2.5f, -0.5f, -5 };
    Triangle* left = TriangleCreate(a, b, c, floorColor, gray, 10);
    SceneAddTriangle(left);

    Vec3 d = { -2.5f, -0.5f, -5 };
    Vec3 e = { 2.5f, -0.5f, 0 };
    Vec3 f = { 2.5f, -0.5f, -5 };
    Triangle* right = TriangleCreate(d, e, f, floorColor, gray, 10);
    SceneAddTriangle(right);

    // Add colored spheres
    Vec3 redSphereCenter = { 1.5f, 0, -2.5f };
    Sphere* redSphere = SphereCreate(redSphereCenter, 0.5f, red, 
                                     gray, 10);
    SceneAddSphere(redSphere);

    Vec3 blueSphereCenter = { 0, 0, -3 };
    Sphere* blueSphere = SphereCreate(blueSphereCenter, 0.5f, blue,
                                      gray, 100);
    SceneAddSphere(blueSphere);

    Vec3 greenSphereCenter = { -1.5f, 0, -2.5f };
    Sphere* greenSphere = SphereCreate(greenSphereCenter, 0.5f, green,
                                       gray, 1000);
    SceneAddSphere(greenSphere);
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
