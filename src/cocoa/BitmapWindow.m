#import "BitmapWindow.h"
#import "BitmapContentView.h"

@implementation BitmapWindow {
    NSWindow* _cocoaWindow;
    BitmapContentView* _contentView;
    NSBitmapImageRep* _imageRep; 
}

- (instancetype)initWithProportionalSize:(NSSize)proportionalSize
{
    self = [super init];
    if (self)
    {
        float width = proportionalSize.width;
        float height = proportionalSize.height;

        NSRect frame = 
           [self.class centeredWindowFrameWithProportionalWidth:width
                                             proportionalHeight:height];
        _cocoaWindow = [self.class createCocoaWindowWithContentRect:frame];

        frame = _cocoaWindow.contentView.frame;
        _imageRep = [self.class createImageRepWithSize:frame.size];
        _contentView = [[BitmapContentView alloc] initWithFrame:frame
                                                      imageRep:_imageRep];

        _cocoaWindow.contentView = _contentView;
    }

    return self;
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

+ (NSRect)centeredWindowFrameWithProportionalWidth:(float)width 
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

+ (NSWindow*)createCocoaWindowWithContentRect:(NSRect)contentRect
{
    NSWindow* window = 
        [[NSWindow alloc] initWithContentRect:contentRect
                                    styleMask:NSWindowStyleMaskTitled
                                      backing:NSBackingStoreBuffered
                                        defer:NO];
   window.title = @"WindowTest";
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
