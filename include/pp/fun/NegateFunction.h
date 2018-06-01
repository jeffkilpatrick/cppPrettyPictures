#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

#include <random>

namespace pp {
    class PP_EXPORT NegateFunction final : public IUnaryFunction {
    public:
        NegateFunction(IFunctionPtr arg);

        float EvalSingle(float x, float y, float a) const override;
        std::string ToString() const override;
    };

    class PP_EXPORT NegateFunctionGenerator final : public IUnaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make(IFunctionPtr arg) override;
    };
}
