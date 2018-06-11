#pragma once

#include "pp/fun/DefaultFunction.h"

#include <cmath>

namespace pp {

    struct AbsTraits {
        static float Eval(float a) { return std::abs(a); }
        static const char* GetName() { return "abs"; }
    };

    using AbsFunction = DefaultUnaryFunction<AbsTraits>;
    using AbsFunctionGenerator = DefaultUnaryFunctionGenerator<AbsFunction>;

    // ---------------------------------------------------------------------

    struct ClipTraits {
        static float Eval(float a)
        {
            a = std::min(a, 1.0f);
            a = std::max(a, -1.0f);
            return a;
        }

        static const char* GetName() { return "clip"; }
    };

    using ClipFunction = DefaultUnaryFunction<ClipTraits>;
    using ClipFunctionGenerator = DefaultUnaryFunctionGenerator<ClipFunction>;

    // ---------------------------------------------------------------------

    struct RoundDownTraits {
        static float Eval(float a) { return std::floor(a); }
        static const char* GetName() { return "floor"; }
    };

    using RoundDownFunction = DefaultUnaryFunction<RoundDownTraits>;
    using RoundDownFunctionGenerator = DefaultUnaryFunctionGenerator<RoundDownFunction>;

    // ---------------------------------------------------------------------

    struct RoundUpTraits {
        static float Eval(float a) { return std::ceil(a); }
        static const char* GetName() { return "ceil"; }
    };

    using RoundUpFunction = DefaultUnaryFunction<RoundUpTraits>;
    using RoundUpFunctionGenerator = DefaultUnaryFunctionGenerator<RoundUpFunction>;

    // ---------------------------------------------------------------------

    struct WrapTraits {
        static float Eval(float a)
        {
            auto n = std::round(a / 2.f);
            return a - (2.f * n);
        }

        static const char* GetName() { return "wrap"; }
    };

    using WrapFunction = DefaultUnaryFunction<WrapTraits>;
    using WrapFunctionGenerator = DefaultUnaryFunctionGenerator<WrapFunction>;
}
