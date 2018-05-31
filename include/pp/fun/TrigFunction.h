#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

#include <random>

namespace pp {

    class AtanFunction : public IUnaryFunction {
    public:
        AtanFunction(IFunctionPtr arg);

        float Eval(float x, float y) const override;
    };

    class AtanFunctionGenerator : public IUnaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make(IFunctionPtr arg) override;
    };

    // ---------------------------------------------------------------------

    class CosFunction : public IUnaryFunction {
    public:
        CosFunction(IFunctionPtr arg);

        float Eval(float x, float y) const override;
    };

    class CosFunctionGenerator : public IUnaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make(IFunctionPtr arg) override;
    };

    // ---------------------------------------------------------------------

    class SinFunction : public IUnaryFunction {
    public:
        SinFunction(IFunctionPtr arg);

        float Eval(float x, float y) const override;
    };

    class SinFunctionGenerator : public IUnaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make(IFunctionPtr arg) override;
    };
}
