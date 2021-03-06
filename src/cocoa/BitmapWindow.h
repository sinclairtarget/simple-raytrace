#import <Cocoa/Cocoa.h>

@interface BitmapWindow : NSObject

@property (readonly, nonatomic) NSRect contentBounds;

- (instancetype)initWithSize:(NSSize)size;
- (instancetype)initWithProportionalSize:(NSSize)proportionalSize;
- (void)setColor:(NSColor*)color atX:(NSUInteger)x y:(NSUInteger)y;
- (void)draw;

@end
