#include <unistd.h>
#include <stdio.h>

#include "platform.h"
#include "vec3.h"
#include "ray.h"
#include "surfaces.h"

int main(int argc, char* argv[])
{
    Vec3 center = { 0, 0, -10 };
    Sphere* sphere = SphereCreate(center, 1);
    
    printf("%s\n", SphereToString(sphere));

    Vec3 origin = { 0, 0, 0 };
    Vec3 direction = { 0, 0, -1 };
    Ray* ray = RayCreate(origin, direction);

    RayHit* hit = SphereIntersect(sphere, ray);
    printf("%s\n", RayHitToString(hit));

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
