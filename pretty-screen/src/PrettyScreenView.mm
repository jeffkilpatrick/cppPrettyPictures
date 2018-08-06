#if defined(OS_MACOSX)

#import "PrettyScreenView.h"

#include "pp/Export.h"
#include "pp/expr/Eval.h"
#include "pp/expr/Generate.h"
#include "pp/serialize/FunctionSerializer.h"

static NSBundle* SaverBundle()
{
    return [NSBundle bundleForClass:[PrettyScreenView class]];
}

static NSString* ModuleName()
{
    return [SaverBundle() bundleIdentifier];
}

static NSString* const DelayKey = @"Delay";
static NSString* const MinDepthKey = @"MinDepth";
static NSString* const MaxDepthKey = @"MaxDepth";
static NSString* const ShowExprKey = @"ShowExpr";

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

    // Serialize the expression
    auto exprStr = pp::Serialize(*expr);
    expression = [NSString stringWithUTF8String:exprStr.c_str()];

    // Turn the expression into pixel values
    auto ppimage = Eval(*expr, 2 * size.width, 2 * size.height);

    // Turn the image into a PNG. BMP would be faster, but the PNG
    // library more easily supports getting the encoded data without
    // creating a temporary file.
    auto pngData = pp::WritePng(ppimage, exprStr);

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
            [NSNumber numberWithInt:3], DelayKey,
            [NSNumber numberWithInt:2], MinDepthKey,
            [NSNumber numberWithInt:5], MaxDepthKey,
            [NSNumber numberWithBool:YES], ShowExprKey,
            nil]];

        [self setAnimationTimeInterval:[defaults integerForKey:DelayKey]];
        self->renderQueue = [[NSOperationQueue alloc] init];
        self->renderer = nil;
    }
    return self;
}

- (void)animateOneFrame
{
    // Create a render op the first time we run
    if (!renderer) {
        renderer = [self makeRenderer];
        [renderQueue addOperation:renderer];
    }

    // Make sure rendering is finished
    [renderer waitUntilFinished];

    // Draw the image into this view
    [renderer.image drawInRect:[self bounds]];

    // Perhaps display the expression
    auto defaults = [ScreenSaverDefaults defaultsForModuleWithName:ModuleName()];
    if ([defaults boolForKey:ShowExprKey]) {
        NSDictionary<NSAttributedStringKey, id>* attrs = @{};
        [renderer.expression drawInRect:[self bounds] withAttributes:attrs];
    }
    NSLog(@"Pretty picture: %@", renderer.expression);

    // Start computing the next image
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
        if (![SaverBundle() loadNibNamed:@"ConfigureSheet" owner:self topLevelObjects:nil]) {
            NSLog(@"Failed to load configure sheet");
            NSBeep();
        }
    }

    auto defaults = [ScreenSaverDefaults defaultsForModuleWithName:ModuleName()];
    [delaySlider setIntValue:(int)[defaults integerForKey:DelayKey]];
    [delayLabel setIntValue:(int)[defaults integerForKey:DelayKey]];
    [minDepthSlider setIntValue:(int)[defaults integerForKey:MinDepthKey]];
    [minDepthLabel setIntValue:(int)[defaults integerForKey:MinDepthKey]];
    [maxDepthSlider setIntValue:(int)[defaults integerForKey:MaxDepthKey]];
    [maxDepthLabel setIntValue:(int)[defaults integerForKey:MaxDepthKey]];
    [showExpressionBox setState:[defaults boolForKey:ShowExprKey]];

    return configSheet;
}

- (IBAction)cancelClick:(id)sender
{
    [[NSApplication sharedApplication] endSheet:configSheet];
}

- (IBAction)okClick:(id)sender
{
    auto defaults = [ScreenSaverDefaults defaultsForModuleWithName:ModuleName()];
    [defaults setInteger:[delaySlider intValue] forKey:DelayKey];
    [defaults setInteger:[minDepthSlider intValue] forKey:MinDepthKey];
    [defaults setInteger:[maxDepthSlider intValue] forKey:MaxDepthKey];
    [defaults setBool:[showExpressionBox state] forKey:ShowExprKey];

    [defaults synchronize];

    [self setAnimationTimeInterval:[defaults integerForKey:DelayKey]];

    [[NSApplication sharedApplication] endSheet:configSheet];
}

@end

#endif
