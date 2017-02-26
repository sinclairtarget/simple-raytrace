#import "../platform.h"
#import "ApplicationDelegate.h"
#import "BitmapWindow.h"

static BitmapWindow* window;

void Init()
{
    @autoreleasepool {
        // Initialize application
        [NSApplication sharedApplication];

        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        [NSApp activateIgnoringOtherApps:YES];

        [[NSApplication sharedApplication] finishLaunching];

        // Manually set an application delegate
        ApplicationDelegate* delegate = [[ApplicationDelegate alloc] init];
        [[NSApplication sharedApplication] setDelegate:delegate];
    }
}

RectSize CreateWindow(float proportionalWidth, float proportionalHeight)
{
    @autoreleasepool {
        NSSize proportionalSize = 
            NSMakeSize(proportionalWidth, proportionalHeight);
        window = 
            [[BitmapWindow alloc] initWithProportionalSize:proportionalSize];
        
        RectSize size;
        size.width = window.contentBounds.size.width;
        size.height = window.contentBounds.size.height;
        return size;
    }
}

void ProcessEvents()
{
    @autoreleasepool {
        // Manually pull events from the event queue, since we're not relying
        // on Cocoa's default NSApplication run loop.
        for (;;) {
            NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                                untilDate:[NSDate distantPast]
                                                   inMode:NSDefaultRunLoopMode
                                                  dequeue:YES];
            if (event != nil) {
                //NSLog(@"Sending event: %@", event);
                [NSApp sendEvent:event];
            }
            else {
                break;
            }
        }
    }
}

void SetColor(int x, int y, Color color)
{
    @autoreleasepool {
        NSColor* cocoaColor = [NSColor colorWithCalibratedRed:color.r 
                                                        green:color.g 
                                                         blue:color.b
                                                        alpha:color.a];
        [window setColor:cocoaColor atX:x y:y];
    }
}

void Draw()
{
    @autoreleasepool {
        [window draw];
    }
}
