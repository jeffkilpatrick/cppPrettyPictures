#import <ScreenSaver/ScreenSaver.h>

#include "pp/expr/Generate.h"
#include "pp/fun/Registry.h"

@interface PrettyScreenView : ScreenSaverView {
    IBOutlet id configSheet;
    IBOutlet id delaySlider;
    IBOutlet id delayLabel;
    IBOutlet id minDepthSlider;
    IBOutlet id minDepthLabel;
    IBOutlet id maxDepthSlider;
    IBOutlet id maxDepthLabel;
    IBOutlet id showExpressionBox;
}

@end
