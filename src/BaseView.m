#import "BaseView.h"

@interface BaseView ()

@property NSImage* imageToDraw;

//@property (readonly) NSBitmapImageRep* bitmap;

@end

@implementation BaseView

- (instancetype)initWithFrame:(NSRect)frameRect image:(NSImage*)image
{
    [super initWithFrame:frameRect];

    self.imageToDraw = image;

//    float width = frameRect.size.width;
//    float height = frameRect.size.height;
//    bitmap = [[NSBitmapImageRep alloc] initWithDataPlanes:NULL
//                                               pixelsWide:width
//                                               pixelsHigh:height
//                                            bitsPerSample:8
//                                          samplesPerPixel:3
//                                                 hasAlpha:NO
    return self;
}


- (void)drawRect:(NSRect)dirtyRect
{
    NSGraphicsContext* context = [NSGraphicsContext currentContext];
    NSLog(@"drawRect with context: %@", context);
    NSLog(@"image: %@", self.imageToDraw);

    NSColor* blue = [NSColor blueColor];

    NSRect rect = NSMakeRect(21, 21, 210, 210);
    [blue set];
    NSRectFill(rect);
}

@end
