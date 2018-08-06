#pragma once

#include "pp/fun/DefaultFunction.h"

namespace pp {

    class ColorNoiseFunction final : public IUnaryFunction
    {
    public:
        struct Traits {
            static const char* GetName() { return "color-noise"; }
        };

        ColorNoiseFunction(IFunctionPtr arg);
        float EvalSingle(float x, float y, float a) const override;
        const std::string& GetName() const override;
    };

    using ColorNoiseFunctionGenerator = DefaultUnaryFunctionGenerator<ColorNoiseFunction>;

    // -------------------------------------------------------------

    class GrayscaleNoiseFunction final : public IFunction
    {
    public:
        struct Traits {
            static const char* GetName() { return "grayscale-noise"; }
        };

        GrayscaleNoiseFunction(IFunctionPtr arg);
        void EvalRow(const std::vector<float>& xs, float y, Color* out) const override;
        const std::string& GetName() const override;
    };

    using GrayscaleNoiseFunctionGenerator = DefaultUnaryFunctionGenerator<GrayscaleNoiseFunction>;
}