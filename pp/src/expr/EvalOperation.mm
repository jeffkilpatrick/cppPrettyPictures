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
