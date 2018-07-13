#if defined(OS_MACOSX)

#import "PrettyScreenView.h"

#include "pp/Export.h"
#include "pp/expr/Eval.h"
#include "pp/expr/Generate.h"
#include "pp/serialize/FunctionSerializer.h"

static NSString* ModuleName()
{
    // TODO-jrk: Get this from the bundle
    return @"org.bouncingsheep.PrettyScreen";
}

static NSString* const MinDepthKey = @"MinDepth";
static NSString* const MaxDepthKey = @"MaxDepth";

@implementation RenderOperation

@synthesize expression;
@synthesize image;

- (instancetype)initWithRegistry:(pp::Registry*)r size:(NSSize)s depth:(pp::Range)d;
{
    self = [super init];

    if (self) {
        image = nil;
        registry = r;
        size = s;
        depth = d;
    }

    return self;
}

-(void)main {
    // Create a random image expression
    auto expr = RandomExpression(*self->registry, self->depth);
    auto exprStr = pp::Serialize(*expr);
    expression = [NSString stringWithUTF8String:exprStr.c_str()];
    expression = [NSString stringWithFormat:@"%@\nDepth: (%d, %d)", expression, self->depth.Min, self->depth.Max];

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
    auto defaults = [ScreenSaverDefaults defaultsForModuleWithName:ModuleName()];
    pp::Range d;
    d.Min = [defaults integerForKey:MinDepthKey];
    d.Max = [defaults integerForKey:MaxDepthKey];

    return [[RenderOperation alloc] initWithRegistry:&registry size:[self bounds].size depth:d];
}

- (instancetype)initWithFrame:(NSRect)frame isPreview:(BOOL)isPreview
{
    self = [super initWithFrame:frame isPreview:isPreview];
    if (self) {

        // Register default values
        auto defaults = [ScreenSaverDefaults defaultsForModuleWithName:ModuleName()];
        [defaults registerDefaults:[NSDictionary dictionaryWithObjectsAndKeys:
            [NSNumber numberWithInt:2], MinDepthKey,
            [NSNumber numberWithInt:5], MaxDepthKey,
            nil]];

        [self setAnimationTimeInterval:3.0];
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

    NSDictionary<NSAttributedStringKey, id>* attrs = @{};
    [renderer.expression drawInRect:[self bounds] withAttributes:attrs];

    renderer = [self makeRenderer];
    [renderQueue addOperation:renderer];
}

- (BOOL)hasConfigureSheet
{
    return YES;
}

- (NSWindow*)configureSheet
{
    if (!configSheet) {
        // TODO-jrk: don't use deprecated API
//        if (![[NSBundle mainBundle] loadNibNamed:@"ConfigureSheet" owner:self topLevelObjects:nil]) {
        if (![NSBundle loadNibNamed:@"ConfigureSheet" owner:self]) {
            NSLog(@"Failed to load configure sheet");
            NSBeep();
        }
    }

    auto defaults = [ScreenSaverDefaults defaultsForModuleWithName:ModuleName()];
    [minDepthSlider setIntValue:(int)[defaults integerForKey:MinDepthKey]];
    [maxDepthSlider setIntValue:(int)[defaults integerForKey:MaxDepthKey]];

    return configSheet;
}

- (IBAction)cancelClick:(id)sender
{
    [[NSApplication sharedApplication] endSheet:configSheet];
}

- (IBAction)okClick:(id)sender
{
    auto defaults = [ScreenSaverDefaults defaultsForModuleWithName:ModuleName()];
    [defaults setInteger:[minDepthSlider intValue] forKey:MinDepthKey];
    [defaults setInteger:[maxDepthSlider intValue] forKey:MaxDepthKey];

    [defaults synchronize];

    [[NSApplication sharedApplication] endSheet:configSheet];
}

@end

#endif
