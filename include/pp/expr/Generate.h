#pragma once

#include "pp/fun/IFunction.h"

namespace pp {
    class Registry;

    struct Range {
        uint16_t Min{1};
        uint16_t Max{5};
    };

    PP_EXPORT IFunctionPtr RandomExpression(Registry& r, Range depth);
}
