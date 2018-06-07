#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

#include <random>

namespace pp {

    class PP_EXPORT AtanFunction final : public IUnaryFunction {
    public:
        AtanFunction(IFunctionPtr arg);

        float EvalSingle(float x, float y, float a) const override;
        const std::string& GetName() const override;
    };

    class PP_EXPORT AtanFunctionGenerator final : public IUnaryFunctionGenerator {
    public:
        IFunctionPtr Make(IFunctionPtr arg) override;
        const std::string& GetName() const override;
    };

    // ---------------------------------------------------------------------

    class PP_EXPORT CosFunction final : public IUnaryFunction {
    public:
        CosFunction(IFunctionPtr arg);

        float EvalSingle(float x, float y, float a) const override;
        const std::string& GetName() const override;
    };

    class PP_EXPORT CosFunctionGenerator final : public IUnaryFunctionGenerator {
    public:
        IFunctionPtr Make(IFunctionPtr arg) override;
        const std::string& GetName() const override;
    };

    // ---------------------------------------------------------------------

    class PP_EXPORT SinFunction final : public IUnaryFunction {
    public:
        SinFunction(IFunctionPtr arg);

        float EvalSingle(float x, float y, float a) const override;
        const std::string& GetName() const override;
    };

    class PP_EXPORT SinFunctionGenerator final : public IUnaryFunctionGenerator {
    public:
        IFunctionPtr Make(IFunctionPtr arg) override;
        const std::string& GetName() const override;
    };
}
