#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

namespace pp {

    class ColorNoiseFunction final : public IFunction
    {
    public:
        ColorNoiseFunction(IFunctionPtr arg);
        Color Eval(float x, float y) const override;
        std::string ToString() const override;

    private:
        IFunctionPtr m_arg;
    };

    class ColorNoiseFunctionGenerator final : public IUnaryFunctionGenerator
    {
    public:
        IFunctionPtr Make(IFunctionPtr arg) override;
    };

    class GrayscaleNoiseFunction final : public IUnaryFunction
    {
    public:
        GrayscaleNoiseFunction(IFunctionPtr arg);
        float EvalSingle(float x, float y, float a) const override;
        std::string ToString() const override;
    };

    class GrayscaleNoiseFunctionGenerator final : public IUnaryFunctionGenerator
    {
    public:
        IFunctionPtr Make(IFunctionPtr arg) override;
    };
}