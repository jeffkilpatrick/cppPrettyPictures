#import "PrettyScreenView.h"

#include "pp/Export.h"
#include "pp/expr/Eval.h"
#include "pp/expr/Generate.h"

@implementation PrettyScreenView

- (instancetype)initWithFrame:(NSRect)frame isPreview:(BOOL)isPreview
{
    self = [super initWithFrame:frame isPreview:isPreview];
    if (self) {
        [self setAnimationTimeInterval:3.0];
        self->maxDepth = 5;
    }
    return self;
}

- (void)startAnimation
{
    [super startAnimation];
}

- (void)stopAnimation
{
    [super stopAnimation];
}

- (void)drawRect:(NSRect)rect
{
    [super drawRect:rect];
}

- (void)animateOneFrame
{
    auto size = [self bounds].size;

    // Create a random image expression
    auto expr = RandomExpression(self->registry, self->maxDepth);

    // Turn the expression into pixel values
    auto image = Eval(*expr, size.width, size.height);

    // Turn the image into a PNG. BMP would be faster, but the PNG
    // library more easily supports getting the encoded data without
    // creating a temporary file.
    auto pngData = pp::WritePng(image);

    // Turn the PNG into an NSImage
    auto nsdata = [NSData dataWithBytes:pngData.data() length:pngData.size()];
    auto nsimage = [[NSImage alloc] initWithData:nsdata];

    // Draw the image
    [nsimage drawInRect:[self bounds]];
}

- (BOOL)hasConfigureSheet
{
    return NO;
}

- (NSWindow*)configureSheet
{
    return nil;
}

@end
