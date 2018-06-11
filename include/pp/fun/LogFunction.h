#pragma once

#include "pp/fun/DefaultFunction.h"

#include <cmath>

namespace pp {

    struct ExpTraits {
        static float Eval(float x, float y, float a)
        {
            if (a > 5.f)
            {
                return std::exp(5.f);
            }

            return std::exp(a);
        }

        static const char* GetName() { return "exp"; }
    };

    using ExpFunction = DefaultUnaryFunction<ExpTraits>;
    using ExpFunctionGenerator = DefaultUnaryFunctionGenerator<ExpFunction>;

    // ---------------------------------------------------------------------

    struct LogTraits {
        static float Eval(float x, float y, float a)
        {
            if (a < 0.f)
            {
                a *= -1.f;
            }

            a = std::max(1e-3f, a);

            return std::log(a);
        }

        static const char* GetName() { return "ln"; }
    };

    using LogFunction = DefaultUnaryFunction<LogTraits>;
    using LogFunctionGenerator = DefaultUnaryFunctionGenerator<LogFunction>;

}
