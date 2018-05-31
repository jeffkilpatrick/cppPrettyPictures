#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

#include <random>

namespace pp {

    class PP_EXPORT XFunction final : public INonaryFunction {
    public:
        float Eval(float x, float y) const override;
        std::string ToString() const override;
    };

    class XFunctionGenerator final : public INonaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make() override;
    };

    // ---------------------------------------------------------------------

    class PP_EXPORT YFunction final : public INonaryFunction {
    public:
        float Eval(float x, float y) const override;
        std::string ToString() const override;
    };

    class YFunctionGenerator final : public INonaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make() override;
    };
}
