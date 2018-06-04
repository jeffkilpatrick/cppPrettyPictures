#include "pp/fun/ColorSpaceFunction.h"

using pp::RgbToYCbCrFunction;
using pp::YCbCrToRgbFunction;

RgbToYCbCrFunction::RgbToYCbCrFunction(IFunctionPtr fun)
    : IFunction({ std::move(fun) })
{ }

pp::Color RgbToYCbCrFunction::Eval(float x, float y) const
{
    auto rgb = GetArgs().at(0)->Eval(x, y);
    return {
         0.2989f * rgb.C1 + 0.5866f * rgb.C2 + 0.1145f * rgb.C3,
        -0.1687f * rgb.C1 - 0.3312f * rgb.C2 + 0.5000f * rgb.C3,
         0.5000f * rgb.C1 - 0.4183f * rgb.C2 - 0.0816f * rgb.C3
    };
}

const std::string& RgbToYCbCrFunction::GetName() const
{
    static std::string name = "rgb-to-ycpcr";
    return name;
}

pp::IFunctionPtr pp::RgbToYCbCrFunctionGenerator::Make(IFunctionPtr fun)
{
    return std::make_unique<RgbToYCbCrFunction>(std::move(fun));
}

// ---------------------------------------------------------------------

YCbCrToRgbFunction::YCbCrToRgbFunction(IFunctionPtr fun)
    : IFunction({ std::move(fun) })
{ }

pp::Color YCbCrToRgbFunction::Eval(float x, float y) const
{
    auto yCbCr = GetArgs().at(0)->Eval(x, y);
    return {
        yCbCr.C1 +                    + 1.4022f * yCbCr.C3,
        yCbCr.C1 - 0.3456f * yCbCr.C2 - 0.7145f * yCbCr.C3,
        yCbCr.C1 + 1.7710f * yCbCr.C2
    };
}

const std::string& YCbCrToRgbFunction::GetName() const
{
    static std::string name = "ycbcr-to-rgb";
    return name;
}

pp::IFunctionPtr pp::YCbCrToRgbFunctionGenerator::Make(IFunctionPtr fun)
{
    return std::make_unique<YCbCrToRgbFunction>(std::move(fun));
}