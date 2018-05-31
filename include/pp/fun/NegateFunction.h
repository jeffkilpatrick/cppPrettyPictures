#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

#include <random>

namespace pp {
    class NegateFunction final : public IUnaryFunction {
    public:
        NegateFunction(IFunctionPtr arg);

        float Eval(float x, float y) const override;
        std::string ToString() const override;
    };

    class NegateFunctionGenerator final : public IUnaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make(IFunctionPtr arg) override;
    };
}
