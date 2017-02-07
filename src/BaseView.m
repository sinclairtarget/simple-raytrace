#import "BaseView.h"

@interface BaseView ()

@property NSImage* imageToDraw;
@property NSImage* renderImage;

@end

@implementation BaseView

- (instancetype)initWithFrame:(NSRect)frameRect image:(NSImage*)image
{
    [super initWithFrame:frameRect];

    self.imageToDraw = image;
    NSLog(@"Initialized with image: %@", self.imageToDraw);

    NSSize renderRectSize = NSMakeSize(256, 256);
    self.renderImage = [self.class createRenderImageWithSize:renderRectSize];

    return self;
}


- (void)drawRect:(NSRect)dirtyRect
{
    NSGraphicsContext* context = [NSGraphicsContext currentContext];
    NSLog(@"drawRect with context: %@", context);

    NSColor* blue = [NSColor blueColor];

    NSRect rect = NSMakeRect(21, 21, 210, 210);
    [blue set];
    NSRectFill(rect);

    [self.imageToDraw drawAtPoint:CGPointMake(0, 0)
                         fromRect:NSZeroRect
                        operation:NSCompositingOperationSourceOver
                         fraction:1];

    [self.renderImage drawAtPoint:CGPointMake(300, 300)
                         fromRect:NSZeroRect
                        operation:NSCompositingOperationSourceOver
                         fraction:1];
}

+ (NSImage*)createRenderImageWithSize:(NSSize)size
{
    NSBitmapImageRep* imageRep = [self.class createImageRepWithSize:size];

    NSColor* renderColor = [NSColor greenColor];
    [self.class drawInImageRep:imageRep
                        inRect:NSMakeRect(0, 0, size.width, size.height)
                     withColor:renderColor];

    return [[NSImage alloc] initWithCGImage:imageRep.CGImage
                                       size:NSZeroSize];
}

+ (NSBitmapImageRep*)createImageRepWithSize:(NSSize)size
{
    return [[NSBitmapImageRep alloc] 
                    initWithBitmapDataPlanes:nil
                                  pixelsWide:size.width
                                  pixelsHigh:size.height
                               bitsPerSample:8
                             samplesPerPixel:4
                                    hasAlpha:YES
                                    isPlanar:NO
                              colorSpaceName:NSCalibratedRGBColorSpace
                                bitmapFormat:0
                                 bytesPerRow:(4 * size.width)
                                bitsPerPixel:32];
}

+ (void)drawInImageRep:(NSBitmapImageRep*)rep 
                inRect:(NSRect)rect
             withColor:(NSColor*)color
{
    for (int x = 0; x < rect.size.width; x++)
    {
        for (int y = 0; y < rect.size.width; y++)
        {
            [rep setColor:color
                      atX:rect.origin.x + x
                        y:rect.origin.y + y];
        }
    }
}

@end
