#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

namespace pp {

    class PP_EXPORT RgbToYCbCrFunction final : public IFunction
    {
    public:
        RgbToYCbCrFunction(IFunctionPtr fun);

        Color Eval(float x, float y) const override;
        const std::string& GetName() const override;
    };

    class PP_EXPORT RgbToYCbCrFunctionGenerator final : public IUnaryFunctionGenerator
    {
    public:
        IFunctionPtr Make(IFunctionPtr fun) override;
        const std::string& GetName() const override;
    };

    // --------------------------------------------------------------------

    class PP_EXPORT YCbCrToRgbFunction final : public IFunction
    {
    public:
        YCbCrToRgbFunction(IFunctionPtr fun);

        Color Eval(float x, float y) const override;
        const std::string& GetName() const override;
    };

    class PP_EXPORT YCbCrToRgbFunctionGenerator final : public IUnaryFunctionGenerator
    {
    public:
        IFunctionPtr Make(IFunctionPtr fun) override;
        const std::string& GetName() const override;
    };
}
