#if defined(OS_MACOSX)

#import "PrettyScreenView.h"

#include "pp/Export.h"
#include "pp/expr/Eval.h"
#include "pp/expr/Generate.h"

@implementation RenderOperation

@synthesize image;

- (instancetype)initWithRegistry:(pp::Registry*)r size:(NSSize)s maxDepth:(size_t)maxD;
{
    self = [super init];

    if (self) {
        image = nil;
        registry = r;
        size = s;
        maxDepth = maxD;
    }

    return self;
}

-(void)main {
    // Create a random image expression
    auto expr = RandomExpression(*self->registry, self->maxDepth);

    // Turn the expression into pixel values
    auto ppimage = Eval(*expr, size.width, size.height);

    // Turn the image into a PNG. BMP would be faster, but the PNG
    // library more easily supports getting the encoded data without
    // creating a temporary file.
    auto pngData = pp::WritePng(ppimage);

    // Turn the PNG into an NSImage
    auto nsdata = [NSData dataWithBytes:pngData.data() length:pngData.size()];
    image = [[NSImage alloc] initWithData:nsdata];
}

@end

#pragma mark ------------------------------------------------------------------

@implementation PrettyScreenView

-(RenderOperation*)makeRenderer {
    return [[RenderOperation alloc] initWithRegistry:&registry size:[self bounds].size maxDepth:maxDepth];
}

- (instancetype)initWithFrame:(NSRect)frame isPreview:(BOOL)isPreview
{
    self = [super initWithFrame:frame isPreview:isPreview];
    if (self) {
        [self setAnimationTimeInterval:3.0];
        self->maxDepth = 5;
        self->renderQueue = [[NSOperationQueue alloc] init];
        self->renderer = nil;
    }
    return self;
}

- (void)animateOneFrame
{
    if (!renderer) {
        renderer = [self makeRenderer];
        [renderQueue addOperation:renderer];
    }

    [renderer waitUntilFinished];

    [renderer.image drawInRect:[self bounds]];

    renderer = [self makeRenderer];
    [renderQueue addOperation:renderer];
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

#endif
