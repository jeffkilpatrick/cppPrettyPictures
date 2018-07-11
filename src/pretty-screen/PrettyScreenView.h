#import <ScreenSaver/ScreenSaver.h>

#include "pp/fun/Registry.h"

@interface RenderOperation : NSOperation {
    pp::Registry* registry;
    NSSize size;
    size_t maxDepth;
}

@property NSImage* image;
@property NSString* expression;

- (instancetype)initWithRegistry:(pp::Registry*)registry size:(NSSize)size maxDepth:(size_t)maxDepth;
@end


@interface PrettyScreenView : ScreenSaverView {
    @private
    pp::Registry registry;
    size_t maxDepth;
    NSOperationQueue* renderQueue;
    RenderOperation* renderer;
}

@end
