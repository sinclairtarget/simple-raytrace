#include <unistd.h>
#include <stdio.h>

#include "platform.h"
#include "vec3.h"
#include "sphere.h"
#include "ray.h"

int main(int argc, char* argv[])
{
    Vec3 a = { 0.5, 0.2, 1.2 };
    Vec3 b = { 0.2, 0.3, 1 };
    Vec3 sum = Vec3Add(a, b);
    printf("sum: %s\n", Vec3ToString(sum));

    Sphere* sphere = SphereCreate(a, 2.3);
    printf("sphere: %s\n", SphereToString(sphere));

    Ray* ray = RayCreate(a, b);
    printf("ray: %s\n", RayToString(ray));

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
