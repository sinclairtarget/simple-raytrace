#import "ApplicationDelegate.h"
#import "BaseView.h" 

const float HORIZONTAL_MARGIN = 0.2f;
const float VERTICAL_MARGIN = 0.2f;
NSString* IMAGE_NAME = @"skyrim_man";
NSString* IMAGE_EXT = @"png";

@implementation ApplicationDelegate

- (void)applicationDidFinishLaunching:(NSNotification*)notification
{
    NSLog(@"Application did finish launching!");

    NSRect frame = [self centeredWindowFrameWithProportionalWidth:0.8f
                                               proportionalHeight:0.8f];
    NSWindow* window = 
        [[NSWindow alloc] initWithContentRect:frame
                          styleMask:NSWindowStyleMaskTitled
                          backing:NSBackingStoreBuffered
                          defer:NO];
   window.title = @"WindowTest";

   NSImage* image = [self.class loadImage];

   NSView* view = [[BaseView alloc] initWithFrame:frame image:image];
   window.contentView = view;

   [window makeKeyAndOrderFront:self];

   NSLog(@"Window content view: %@", window.contentView);
}

- (NSRect)centeredWindowFrameWithProportionalWidth:(float)width 
                                proportionalHeight:(float)height
{
    NSRect visibleFrame = [[NSScreen mainScreen] visibleFrame];

    float windowFrameWidth = visibleFrame.size.width * width;
    float windowFrameHeight = visibleFrame.size.height * height;

    float centerX = visibleFrame.size.width / 2;
    float centerY = visibleFrame.size.height / 2;

    float originX = centerX - (windowFrameWidth / 2);
    float originY = centerY - (windowFrameHeight / 2);

    return NSMakeRect(originX, originY, windowFrameWidth, windowFrameHeight);
}

+ (NSImage*)loadImage
{
    NSString* imagePath = [[NSBundle mainBundle] pathForResource:IMAGE_NAME
                                                          ofType:IMAGE_EXT];
    NSLog(@"imagePath: %@", imagePath);

    NSImage* image = [[NSImage alloc] initWithContentsOfFile:imagePath];
    return image;
}

@end 
