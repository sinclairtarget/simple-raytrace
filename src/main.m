#import <Cocoa/Cocoa.h>
#import "ApplicationDelegate.h"

int main(int argc, char* argv[])
{
    // Initialize application
    [NSApplication sharedApplication];

    // Manually set an application delegate
    ApplicationDelegate* delegate = [[ApplicationDelegate alloc] init];
    [[NSApplication sharedApplication] setDelegate:delegate];

    // Run application
    [[NSApplication sharedApplication] run];

    return 0;
}
