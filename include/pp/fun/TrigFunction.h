#pragma once

#include "pp/fun/DefaultFunction.h"

#include <cmath>

namespace pp {

    struct AtanTraits {
        static float Eval(float a) { return std::atan(a); }
        static const char* GetName() { return "atan"; }
    };

    using AtanFunction = DefaultUnaryFunction<AtanTraits>;
    using AtanFunctionGenerator = DefaultUnaryFunctionGenerator<AtanFunction>;

    // ---------------------------------------------------------------------

    struct CosTraits {
        static float Eval(float a) { return std::cos(a); }
        static const char* GetName() { return "cos"; }
    };

    using CosFunction = DefaultUnaryFunction<CosTraits>;
    using CosFunctionGenerator = DefaultUnaryFunctionGenerator<CosFunction>;

    // ---------------------------------------------------------------------

    struct SinTraits {
        static float Eval(float a) { return std::sin(a); }
        static const char* GetName() { return "sin"; }
    };

    using SinFunction = DefaultUnaryFunction<SinTraits>;
    using SinFunctionGenerator = DefaultUnaryFunctionGenerator<SinFunction>;
}
