#import "BitmapContentView.h"

@implementation BitmapContentView {
    NSBitmapImageRep* _imageRep;
}

- (instancetype)initWithFrame:(NSRect)frameRect 
                     imageRep:(NSBitmapImageRep*)imageRep
{
    self = [super initWithFrame:frameRect];

    if (self) 
    {
        _imageRep = imageRep;
    }

    return self;
}


- (void)drawRect:(NSRect)dirtyRect
{
    NSImage* renderImage = [[NSImage alloc] initWithCGImage:_imageRep.CGImage
                                                       size:NSZeroSize];
    [renderImage drawAtPoint:CGPointZero
                    fromRect:NSZeroRect
                   operation:NSCompositingOperationSourceOver
                    fraction:1];
}

@end
