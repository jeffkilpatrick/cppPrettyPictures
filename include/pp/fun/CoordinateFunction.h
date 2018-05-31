#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

#include <random>

namespace pp {

    class XFunction : public INonaryFunction {
    public:
        float Eval(float x, float y) const override;
    };

    class XFunctionGenerator : public INonaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make() override;
    };

    // ---------------------------------------------------------------------

    class YFunction : public INonaryFunction {
    public:
        float Eval(float x, float y) const override;
    };

    class YFunctionGenerator : public INonaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make() override;
    };

}
