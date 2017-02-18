#include "platform.h"
#include "unistd.h"

int main(int argc, char* argv[])
{
    init();
    RectSize size = createWindow(0.8f, 0.8f);

    Color red = { 1, 0, 0, 1 };

    int x = 0;
    int y = 0;

    for (;;) {
        processEvents();

        if (x < size.width && y < size.height) {
            draw(x, y, red);
            x += 1;
            y += 1;
        }
        
        usleep((1.0f/60) * 1000000);
    }

    return 0;
}
