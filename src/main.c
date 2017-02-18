#include "platform.h"
#include "unistd.h"

int main(int argc, char* argv[])
{
    init();
    createWindow(0.8f, 0.8f);

    for (;;) {
        processEvents();
        usleep((1.0f/60) * 1000000);
    }

    //    NSRect bounds = bitmapWindow.contentBounds;
    //
    //    NSColor* blue = [NSColor blueColor];
    //    for (int y = 0; y < bounds.size.height; y++)
    //    {
    //        for (int x = 0; x < bounds.size.width; x++)
    //        {
    //            [bitmapWindow setColor:blue atX:x y:y];
    //        }
    //
    //        if (y % 100 == 0) 
    //        {
    //            [bitmapWindow draw];
    //            [NSThread sleepForTimeInterval:0.5];
    //        }
    //    }

    return 0;
}
