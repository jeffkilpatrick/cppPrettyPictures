#import <ScreenSaver/ScreenSaver.h>

#include "pp/expr/Generate.h"
#include "pp/fun/Registry.h"

@interface RenderOperation : NSOperation {
    pp::Registry* registry;
    NSSize size;
    pp::Range depth;
}

@property NSImage* image;
@property NSString* expression;

- (instancetype)initWithRegistry:(pp::Registry*)registry size:(NSSize)size depth:(pp::Range)depth;
@end


@interface PrettyScreenView : ScreenSaverView {
    IBOutlet id configSheet;
    IBOutlet id delaySlider;
    IBOutlet id delayLabel;
    IBOutlet id minDepthSlider;
    IBOutlet id minDepthLabel;
    IBOutlet id maxDepthSlider;
    IBOutlet id maxDepthLabel;
    IBOutlet id showExpressionBox;

@private
    pp::Registry registry;
    NSOperationQueue* renderQueue;
    RenderOperation* renderer;
}

@end
