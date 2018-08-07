//
//  PrettyPictureView.m
//  PrettyViewer
//
//  Created by Jeff Kilpatrick on 8/6/18.
//  Copyright © 2018 Jeff Kilpatrick. All rights reserved.
//

#import "PrettyPictureView.h"

#import "pp/expr/EvalOperation.h"

@implementation PrettyPictureView {
    pp::Registry _registry;
    NSOperationQueue* _renderQueue;
    EvalOperation* _renderer;
}

- (EvalOperation*)makeEvaluator {
    pp::Range d;
    d.Min = 4;
    d.Max = 10;

    return [[EvalOperation alloc] initWithRegistry:&_registry size:[self bounds].size depth:d];
}

- (void)awakeFromNib {
    _renderQueue = [[NSOperationQueue alloc] init];
    _renderer = nil;
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Create a render op the first time we run
    if (!_renderer) {
        _renderer = [self makeEvaluator];
        [_renderQueue addOperation:_renderer];
    }

    // Make sure rendering is finished
    [_renderer waitUntilFinished];

    // Draw the image into this view
    [_renderer.image drawInRect:[self bounds]];

#if 0
    // Perhaps display the expression
    auto defaults = [ScreenSaverDefaults defaultsForModuleWithName:ModuleName()];
    if ([defaults boolForKey:ShowExprKey]) {
        NSDictionary<NSAttributedStringKey, id>* attrs = @{};
        [_renderer.expression drawInRect:[self bounds] withAttributes:attrs];
    }
#endif
    NSLog(@"Pretty picture: %@", _renderer.expression);

    // Start computing the next image
    _renderer = [self makeEvaluator];
    [_renderQueue addOperation:_renderer];
}

@end
