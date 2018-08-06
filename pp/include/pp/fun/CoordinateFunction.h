#pragma once

#include "pp/fun/DefaultFunction.h"

namespace pp {

    struct XTraits {
        static float Eval(float x, float y) { return x; }
        static const char* GetName() { return "x"; }
    };

    using XFunction = DefaultNonaryFunction<XTraits>;
    using XFunctionGenerator = DefaultNonaryFunctionGenerator<XFunction>;

    // ---------------------------------------------------------------------

    struct YTraits {
        static float Eval(float x, float y) { return y; }
        static const char* GetName() { return "y"; }
    };

    using YFunction = DefaultNonaryFunction<YTraits>;
    using YFunctionGenerator = DefaultNonaryFunctionGenerator<YFunction>;
}
