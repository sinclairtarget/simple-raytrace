#import "BitmapWindow.h"
#import "BitmapContentView.h"

@implementation BitmapWindow {
    NSWindow* _cocoaWindow;
    BitmapContentView* _contentView;
    NSBitmapImageRep* _imageRep; 
}

- (instancetype)initWithSize:(NSSize)size
{
    self = [super init];
    if (self)
    {
        NSRect frame = [self.class centeredWindowFrameWithSize:size];
        _cocoaWindow = [self.class createCocoaWindowWithContentRect:frame];

        frame = _cocoaWindow.contentView.frame;
        _imageRep = [self.class createImageRepWithSize:frame.size];
        _contentView = [[BitmapContentView alloc] initWithFrame:frame
                                                       imageRep:_imageRep];

        _cocoaWindow.contentView = _contentView;
    }

    return self;
}

- (instancetype)initWithProportionalSize:(NSSize)proportionalSize
{
    float width = proportionalSize.width;
    float height = proportionalSize.height;

    NSSize frameSize = 
        [self.class centeredWindowSizeWithProportionalWidth:width
                                         proportionalHeight:height];

    return [self initWithSize:frameSize];
}

- (NSRect)contentBounds
{
    return _contentView.bounds;
}

- (void)setColor:(NSColor*)color atX:(NSUInteger)x y:(NSUInteger)y
{
    [_imageRep setColor:color atX:x y:y];
}

- (void)draw
{
    _contentView.needsDisplay = YES;
    [_cocoaWindow display];
}

+ (NSRect)centeredWindowFrameWithSize:(NSSize)size
{
    NSRect visibleFrame = [[NSScreen mainScreen] visibleFrame];

    float centerX = visibleFrame.size.width / 2;
    float centerY = visibleFrame.size.height / 2;

    float originX = centerX - (size.width / 2);
    float originY = centerY - (size.height / 2);

    return NSMakeRect(originX, originY, size.width, size.height);
}

+ (NSSize)centeredWindowSizeWithProportionalWidth:(float)width 
                               proportionalHeight:(float)height
{
    NSRect visibleFrame = [[NSScreen mainScreen] visibleFrame];

    float windowFrameWidth = visibleFrame.size.width * width;
    float windowFrameHeight = visibleFrame.size.height * height;

    return NSMakeSize(windowFrameWidth, windowFrameHeight);
}

+ (NSWindow*)createCocoaWindowWithContentRect:(NSRect)contentRect
{
    NSWindow* window = 
        [[NSWindow alloc] initWithContentRect:contentRect
                                    styleMask:NSWindowStyleMaskTitled
                                      backing:NSBackingStoreBuffered
                                        defer:NO];
   window.title = @"SimpleRaytrace";
   [window makeKeyAndOrderFront:self];

   return window;
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

@end
