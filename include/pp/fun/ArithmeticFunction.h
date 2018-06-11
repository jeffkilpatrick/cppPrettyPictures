#pragma once

#include "pp/fun/DefaultFunction.h"

#include <cmath>

namespace pp {

    // ---------------------------------------------------------------------------

    struct AddTraits {
        static float Eval(float a0, float a1) { return a0 + a1; }
        static const char* GetName() { return "add"; }
    };

    using AddFunction = DefaultBinaryFunction<AddTraits>;
    using AddFunctionGenerator = DefaultBinaryFunctionGenerator<AddFunction>;

    // ---------------------------------------------------------------------------

    struct SubtractTraits {
        static float Eval(float a0, float a1) { return a0 - a1; }
        static const char* GetName() { return "sub"; }
    };

    using SubtractFunction = DefaultBinaryFunction<SubtractTraits>;
    using SubtractFunctionGenerator = DefaultBinaryFunctionGenerator<SubtractFunction>;

    // ---------------------------------------------------------------------------

    struct MultiplyTraits {
        static float Eval(float a0, float a1) { return a0 * a1; }
        static const char* GetName() { return "mul"; }
    };

    using MultiplyFunction = DefaultBinaryFunction<MultiplyTraits>;
    using MultiplyFunctionGenerator = DefaultBinaryFunctionGenerator<MultiplyFunction>;

    // ---------------------------------------------------------------------------

    struct DivideTraits {
        static float Eval(float a0, float a1)
        {
            if (std::abs(a1) < 1e-3f)
            {
                a1 = std::copysign(1e-3f, a1);
            }

            return a0 / a1;
        }
        static const char* GetName() { return "div"; }
    };

    using DivideFunction = DefaultBinaryFunction<DivideTraits>;
    using DivideFunctionGenerator = DefaultBinaryFunctionGenerator<DivideFunction>;
}
