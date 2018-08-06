#pragma once

#include "pp/fun/IFunction.h"

#include <ios>

namespace pp {
    PP_EXPORT std::string Serialize(const IFunction& fun);
    PP_EXPORT std::ostream& operator<<(std::ostream& s, const IFunction& fun);
}