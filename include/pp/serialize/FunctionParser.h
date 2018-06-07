#pragma once

#include "pp/fun/IFunction.h"

namespace pp {
    class Registry;

    IFunctionPtr PP_EXPORT Parse(std::string&& str, const pp::Registry& registry);
}