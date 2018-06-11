#pragma once

#include "pp/fun/DefaultFunction.h"

namespace pp {

    class PP_EXPORT RgbToYCbCrFunction final : public IFunction
    {
    public:
        struct Traits {
            static const char* GetName() { return "rgb-to-ycbcr"; }
        };

        RgbToYCbCrFunction(IFunctionPtr fun);

        void EvalRow(const std::vector<float>& xs, float y, Color* out) const override;
        const std::string& GetName() const override;
    };

    using RgbToYCbCrFunctionGenerator = DefaultUnaryFunctionGenerator<RgbToYCbCrFunction>;

    // --------------------------------------------------------------------

    class PP_EXPORT YCbCrToRgbFunction final : public IFunction
    {
    public:
        struct Traits {
            static const char* GetName() { return "ycbcr-to-rgb"; }
        };

        YCbCrToRgbFunction(IFunctionPtr fun);

        void EvalRow(const std::vector<float>& xs, float y, Color* out) const override;
        const std::string& GetName() const override;
    };

    using YCbCrToRgbFunctionGenerator = DefaultUnaryFunctionGenerator<YCbCrToRgbFunction>;
}
