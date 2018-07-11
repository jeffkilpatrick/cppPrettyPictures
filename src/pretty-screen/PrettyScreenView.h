#import <ScreenSaver/ScreenSaver.h>

#include "pp/fun/Registry.h"

@interface PrettyScreenView : ScreenSaverView {
    @private pp::Registry registry;
    @private size_t maxDepth;
}

@end
