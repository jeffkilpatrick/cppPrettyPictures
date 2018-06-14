#pragma once

#include "pp/fun/IFunction.h"

namespace pp {
    class Registry;

    PP_EXPORT IFunctionPtr RandomExpression(Registry& r, size_t maxDepth = 20);
}
