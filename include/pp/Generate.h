#pragma once

#include <memory>

namespace pp {

    class Registry;
    using IFunctionPtr = std::unique_ptr<class IFunction>;

    IFunctionPtr RandomExpression(Registry& r);
}
