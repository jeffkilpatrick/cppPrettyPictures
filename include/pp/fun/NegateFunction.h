#pragma once

#include "pp/fun/DefaultFunction.h"

namespace pp {
    struct NegateTraits {
        static float Eval(float x, float y, float a) { return -1.f * a; }
        static const char* GetName() { return "neg"; }
    };

    using NegateFunction = DefaultUnaryFunction<NegateTraits>;
    using NegateFunctionGenerator = DefaultUnaryFunctionGenerator<NegateFunction>;
}
