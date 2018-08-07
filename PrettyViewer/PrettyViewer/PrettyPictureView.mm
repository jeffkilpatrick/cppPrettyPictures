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
    pp::IFunctionPtr _expr;

    NSOperationQueue* _renderQueue;
    EvalOperation* _renderer;
}

- (EvalOperation*)makeEvaluator {
    return [[EvalOperation alloc] initWithExpression:_expr size:[self bounds].size];
}

- (void)awakeFromNib {
    _renderQueue = [[NSOperationQueue alloc] init];
    _renderer = nil;

    pp::Range d;
    d.Min = 4;
    d.Max = 10;

    _expr = RandomExpression(_registry, d);
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Create a render op the first time we run
    if (!_renderer) {
        _renderer = [self makeEvaluator];
        [_renderQueue addOperation:_renderer];
    }

    NSLog(@"Pretty picture: %@", _renderer.expression);

    // Make sure rendering is finished
    [_renderer waitUntilFinished];

    // Draw the image into this view
    [_renderer.image drawInRect:[self bounds]];
}

@end
