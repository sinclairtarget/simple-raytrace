#include <unistd.h>
#include <stdio.h>

#include "platform.h"
#include "vec3.h"
#include "sphere.h"
#include "ray.h"

int main(int argc, char* argv[])
{
    Vec3 a = { 2.3, 1, 1.34 };
    Vec3 b = { 1, 3, 1 };

    float p = Vec3Dot(a, b);
    printf("p: %f\n", p);

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
