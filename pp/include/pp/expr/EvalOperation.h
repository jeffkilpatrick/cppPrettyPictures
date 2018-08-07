//
//  EvalOp.h
//  pp
//
//  Created by Jeff Kilpatrick on 8/6/18.
//  Copyright © 2018 Jeff Kilpatrick. All rights reserved.
//

#pragma once

#import <Foundation/Foundation.h>

#import "pp/expr/Generate.h"
#import "pp/fun/Registry.h"

@interface EvalOperation : NSOperation

@property (strong, nonatomic) NSImage* image;
@property (strong, nonatomic) NSString* expression;

- (instancetype)initWithRegistry:(pp::Registry*)registry size:(NSSize)size depth:(pp::Range)depth;
- (instancetype)initWithExpression:(pp::IFunctionPtr)expr size:(NSSize)size;
@end

