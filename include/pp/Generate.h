#pragma once

#include "pp/utility/Exports.h"

#include <memory>

namespace pp {

    class Registry;
    using IFunctionPtr = std::unique_ptr<class IFunction>;

    PP_EXPORT IFunctionPtr RandomExpression(Registry& r, size_t maxDepth = 20);
}
