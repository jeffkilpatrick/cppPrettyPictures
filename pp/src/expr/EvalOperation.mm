//
//  EvalOp.m
//  pp
//
//  Created by Jeff Kilpatrick on 8/6/18.
//  Copyright © 2018 Jeff Kilpatrick. All rights reserved.
//

#import "pp/expr/EvalOperation.h"

#import "pp/Export.h"
#import "pp/expr/Eval.h"
#import "pp/serialize/FunctionSerializer.h"

#import <Cocoa/Cocoa.h>

@implementation EvalOperation
{
    pp::Registry* _registry;
    pp::Range _depth;
    NSSize _size;
    pp::IFunctionPtr _expr;
}

@synthesize expression;
@synthesize image;

- (instancetype)initWithRegistry:(pp::Registry*)r size:(NSSize)s depth:(pp::Range)d;
{
    self = [super init];

    if (self) {
        image = nil;
        _registry = r;
        _depth = d;
        _size = s;
        _duration = nil;

        _expr = RandomExpression(*_registry, _depth);

        auto exprStr = pp::Serialize(*_expr);
        expression = [NSString stringWithUTF8String:exprStr.c_str()];
    }

    return self;
}

- (instancetype)initWithExpression:(pp::IFunctionPtr)expr size:(NSSize)size {
    self = [super init];

    if (self) {
        _registry = nil;
        _size = size;
        _expr = std::move(expr);
        _duration = nil;

        auto exprStr = pp::Serialize(*_expr);
        expression = [NSString stringWithUTF8String:exprStr.c_str()];
    }

    return self;
}

- (void)main {
    auto start = [NSDate date];

    // Turn the expression into pixel values
    auto ppimage = Eval(*_expr, 2 * _size.width, 2 * _size.height);

    // Turn the image into a PNG. BMP would be faster, but the PNG
    // library more easily supports getting the encoded data without
    // creating a temporary file.
    auto pngData = pp::WritePng(ppimage, [expression UTF8String]);

    // Turn the PNG into an NSImage
    auto nsdata = [NSData dataWithBytes:pngData.data() length:pngData.size()];
    image = [[NSImage alloc] initWithData:nsdata];

    _duration = [NSNumber numberWithDouble:-1.0 * start.timeIntervalSinceNow];
}

@end
