#import "../platform.h"
#import "ApplicationDelegate.h"
#import "BitmapWindow.h"

static BitmapWindow* window;

void init()
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

void createWindow(float proportionalWidth, float proportionalHeight)
{
    NSLog(@"Creating window...");
    NSSize proportionalSize = NSMakeSize(proportionalWidth, proportionalHeight);
    window = [[BitmapWindow alloc] initWithProportionalSize:proportionalSize];
}

void processEvents()
{
    // Manually pull events from the event queue, since we're not relying on
    // Cocoa's default NSApplication run loop.
    for (;;) {
        NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                            untilDate:[NSDate distantPast]
                                               inMode:NSDefaultRunLoopMode
                                              dequeue:YES];
        if (event != nil) {
            NSLog(@"Sending event: %@", event);
            [NSApp sendEvent:event];
        }
        else {
            break;
        }
    }
}

void draw(int x, int y, float r, float g, float b, float a)
{
    NSColor* color = [NSColor colorWithSRGBRed:r green:g blue:b alpha:a];
    [window setColor:color atX:x y:y];
}
