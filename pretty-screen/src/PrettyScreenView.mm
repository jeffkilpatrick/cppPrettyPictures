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

#pragma mark ------------------------------------------------------------------

@interface RenderOperation : NSOperation

@property (strong, nonatomic) NSImage* image;
@property (strong, nonatomic) NSString* expression;

- (instancetype)initWithRegistry:(pp::Registry*)registry size:(NSSize)size depth:(pp::Range)depth;
@end

@implementation RenderOperation
{
    pp::Registry* _registry;
    NSSize _size;
    pp::Range _depth;
}

@synthesize expression;
@synthesize image;

- (instancetype)initWithRegistry:(pp::Registry*)r size:(NSSize)s depth:(pp::Range)d;
{
    self = [super init];

    if (self) {
        image = nil;
        _registry = r;
        _size = s;
        _depth = d;
    }

    return self;
}

-(void)main {
    // Create a random image expression
    auto expr = RandomExpression(*_registry, _depth);

    // Serialize the expression
    auto exprStr = pp::Serialize(*expr);
    expression = [NSString stringWithUTF8String:exprStr.c_str()];

    // Turn the expression into pixel values
    auto ppimage = Eval(*expr, 2 * _size.width, 2 * _size.height);

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
{
    pp::Registry _registry;
    NSOperationQueue* _renderQueue;
    RenderOperation* _renderer;
}

-(RenderOperation*)makeRenderer {
    auto defaults = [ScreenSaverDefaults defaultsForModuleWithName:ModuleName()];
    pp::Range d;
    d.Min = [defaults integerForKey:MinDepthKey];
    d.Max = [defaults integerForKey:MaxDepthKey];

    return [[RenderOperation alloc] initWithRegistry:&_registry size:[self bounds].size depth:d];
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
        _renderQueue = [[NSOperationQueue alloc] init];
        _renderer = nil;
    }

    return self;
}

- (void)animateOneFrame
{
    // Create a render op the first time we run
    if (!_renderer) {
        _renderer = [self makeRenderer];
        [_renderQueue addOperation:_renderer];
    }

    // Make sure rendering is finished
    [_renderer waitUntilFinished];

    // Draw the image into this view
    [_renderer.image drawInRect:[self bounds]];

    // Perhaps display the expression
    auto defaults = [ScreenSaverDefaults defaultsForModuleWithName:ModuleName()];
    if ([defaults boolForKey:ShowExprKey]) {
        NSDictionary<NSAttributedStringKey, id>* attrs = @{};
        [_renderer.expression drawInRect:[self bounds] withAttributes:attrs];
    }
    NSLog(@"Pretty picture: %@", _renderer.expression);

    // Start computing the next image
    _renderer = [self makeRenderer];
    [_renderQueue addOperation:_renderer];
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
