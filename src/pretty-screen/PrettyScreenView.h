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
    @private
    pp::Registry registry;
    pp::Range depth;
    NSOperationQueue* renderQueue;
    RenderOperation* renderer;
}

@end
