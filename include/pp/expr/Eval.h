#pragma once

#include "pp/Image.h"
#include "pp/utility/Exports.h"

namespace pp {
    class IFunction;

    PP_EXPORT pp::Image Eval(const pp::IFunction& f, size_t width, size_t height);
}
