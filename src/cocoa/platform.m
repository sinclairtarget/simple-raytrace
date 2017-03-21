#import "../platform.h"
#import "ApplicationDelegate.h"
#import "BitmapWindow.h"

static ApplicationDelegate* appDelegate;
static BitmapWindow* window;

void Init()
{
    @autoreleasepool {
        // Initialize application
        [NSApplication sharedApplication];

        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        [NSApp activateIgnoringOtherApps:YES];

        // Manually set an application delegate
        appDelegate = [[ApplicationDelegate alloc] init];
        [NSApp setDelegate:appDelegate];

        [NSApp finishLaunching];
    }
}

RectSize CreateWindow(float width, float height)
{
    @autoreleasepool {
        NSSize frameSize = NSMakeSize(width, height);
        window = [[BitmapWindow alloc] initWithSize:frameSize];

        RectSize size;
        size.width = window.contentBounds.size.width;
        size.height = window.contentBounds.size.height;
        return size;
    }
}

RectSize CreateWindowProportional(float proportionalWidth, 
                                  float proportionalHeight)
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
