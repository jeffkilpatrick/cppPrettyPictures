#import "PrettyScreenView.h"

#include "pp/expr/EvalOperation.h"

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

@implementation PrettyScreenView
{
    pp::Registry _registry;
    NSOperationQueue* _renderQueue;
    EvalOperation* _renderer;
}

-(EvalOperation*)makeEvaluator {
    auto defaults = [ScreenSaverDefaults defaultsForModuleWithName:ModuleName()];
    pp::Range d;
    d.Min = [defaults integerForKey:MinDepthKey];
    d.Max = [defaults integerForKey:MaxDepthKey];

    return [[EvalOperation alloc] initWithRegistry:&_registry size:[self bounds].size depth:d];
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
        _renderer = [self makeEvaluator];
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
    _renderer = [self makeEvaluator];
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
