#import <Cocoa/Cocoa.h>

@interface BitmapContentView : NSView

- (instancetype)initWithFrame:(NSRect)frameRect 
                     imageRep:(NSBitmapImageRep*)imageRep;

@end
