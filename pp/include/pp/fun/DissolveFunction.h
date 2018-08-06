#pragma once

#include "pp/fun/DefaultFunction.h"
#include "pp/fun/RoundFunction.h"

#include <cmath>

namespace pp {

    struct DissolveTraits {
        static float Eval(float x, float y, float a0, float a1, float a2)
        {
            a2 = std::abs(WrapTraits::Eval(x, y, a2));

            return a0 * a2 + a1 * (1.0 - a2);
        }

        static const char* GetName() { return "dissolve"; }
    };

    using DissolveFunction = DefaultTrinaryFunction<DissolveTraits>;
    using DissolveFunctionGenerator = DefaultTrinaryFunctionGenerator<DissolveFunction>;
}