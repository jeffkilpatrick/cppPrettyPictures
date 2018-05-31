#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

#include <random>

namespace pp {
    class RoundDownFunction : public IUnaryFunction {
    public:
        RoundDownFunction(IFunctionPtr arg);

        float Eval(float x, float y) const override;
    };

    class RoundDownFunctionGenerator : public IUnaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make(IFunctionPtr arg) override;
    };

    // ---------------------------------------------------------------------

    class RoundUpFunction : public IUnaryFunction {
    public:
        RoundUpFunction(IFunctionPtr arg);

        float Eval(float x, float y) const override;
    };

    class RoundUpFunctionGenerator : public IUnaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make(IFunctionPtr arg) override;
    };
}
