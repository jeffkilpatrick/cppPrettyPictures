#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

namespace pp {
    class PP_EXPORT NegateFunction final : public IUnaryFunction {
    public:
        NegateFunction(IFunctionPtr arg);

        float EvalSingle(float x, float y, float a) const override;
        const std::string& GetName() const override;
    };

    class PP_EXPORT NegateFunctionGenerator final : public IUnaryFunctionGenerator {
    public:
        IFunctionPtr Make(IFunctionPtr arg) override;
        const std::string& GetName() const override;
    };
}
