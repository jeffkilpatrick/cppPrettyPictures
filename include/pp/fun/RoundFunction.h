#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

#include <random>

namespace pp {
    class PP_EXPORT RoundDownFunction final : public IUnaryFunction {
    public:
        RoundDownFunction(IFunctionPtr arg);

        float Eval(float x, float y) const override;
        std::string ToString() const override;
    };

    class PP_EXPORT RoundDownFunctionGenerator final : public IUnaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make(IFunctionPtr arg) override;
    };

    // ---------------------------------------------------------------------

    class PP_EXPORT RoundUpFunction final : public IUnaryFunction {
    public:
        RoundUpFunction(IFunctionPtr arg);

        float Eval(float x, float y) const override;
        std::string ToString() const override;
    };

    class PP_EXPORT RoundUpFunctionGenerator final : public IUnaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make(IFunctionPtr arg) override;
    };
}
