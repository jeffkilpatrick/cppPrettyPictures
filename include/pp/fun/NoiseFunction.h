#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

namespace pp {

    class ColorNoiseFunction final : public IUnaryFunction
    {
    public:
        ColorNoiseFunction(IFunctionPtr arg);
        float EvalSingle(float x, float y, float a) const override;
        const std::string& GetName() const override;
    };

    class ColorNoiseFunctionGenerator final : public IUnaryFunctionGenerator
    {
    public:
        IFunctionPtr Make(IFunctionPtr arg) override;
        const std::string& GetName() const override;
    };

    // -------------------------------------------------------------

    class GrayscaleNoiseFunction final : public IFunction
    {
    public:
        GrayscaleNoiseFunction(IFunctionPtr arg);
        Color Eval(float x, float y) const override;
        void EvalRow(const std::vector<float>& xs, float y, Color* out) const override;
        const std::string& GetName() const override;
    };

    class GrayscaleNoiseFunctionGenerator final : public IUnaryFunctionGenerator
    {
    public:
        IFunctionPtr Make(IFunctionPtr arg) override;
        const std::string& GetName() const override;
    };
}