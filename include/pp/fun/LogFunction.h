#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

#include <random>

namespace pp {
    class PP_EXPORT ExpFunction final : public IUnaryFunction {
    public:
        ExpFunction(IFunctionPtr arg);

        float EvalSingle(float x, float y, float a) const override;
        std::string ToString() const override;
    };

    class PP_EXPORT ExpFunctionGenerator final : public IUnaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make(IFunctionPtr arg) override;
    };

    // ---------------------------------------------------------------------

    class PP_EXPORT LogFunction final : public IUnaryFunction {
    public:
        LogFunction(IFunctionPtr arg);

        float EvalSingle(float x, float y, float a) const override;
        std::string ToString() const override;
    };

    class PP_EXPORT LogFunctionGenerator final : public IUnaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make(IFunctionPtr arg) override;
    };

}
