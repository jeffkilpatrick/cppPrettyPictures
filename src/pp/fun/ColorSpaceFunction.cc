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

void RgbToYCbCrFunction::EvalRow(const std::vector<float>& xs, float y, pp::Color* out) const
{
    auto& buf = m_buffers.at(0);
    buf.resize(xs.size(), Color{0.f});

    GetArgs().at(0)->EvalRow(xs, y, buf.data());

    for (size_t i = 0; i < xs.size(); ++i)
    {
        *out = Color {
             0.2989f * buf[i].C1 + 0.5866f * buf[i].C2 + 0.1145f * buf[i].C3,
            -0.1687f * buf[i].C1 - 0.3312f * buf[i].C2 + 0.5000f * buf[i].C3,
             0.5000f * buf[i].C1 - 0.4183f * buf[i].C2 - 0.0816f * buf[i].C3
        };
        ++out;
    }
}

const std::string& RgbToYCbCrFunction::GetName() const
{
    return RgbToYCbCrFunctionGenerator{}.GetName();
}

pp::IFunctionPtr pp::RgbToYCbCrFunctionGenerator::Make(IFunctionPtr fun)
{
    return std::make_unique<RgbToYCbCrFunction>(std::move(fun));
}

const std::string& pp::RgbToYCbCrFunctionGenerator::GetName() const
{
    static std::string name = "rgb-to-ycbcr";
    return name;
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

void YCbCrToRgbFunction::EvalRow(const std::vector<float>& xs, float y, pp::Color* out) const
{
    auto& buf = m_buffers.at(0);
    buf.resize(xs.size(), Color{0.f});

    GetArgs().at(0)->EvalRow(xs, y, buf.data());

    for (size_t i = 0; i < xs.size(); ++i)
    {
        *out = Color {
            buf[i].C1 +                     + 1.4022f * buf[i].C3,
            buf[i].C1 - 0.3456f * buf[i].C2 - 0.7145f * buf[i].C3,
            buf[i].C1 + 1.7710f * buf[i].C2
        };
        ++out;
    }
}

const std::string& YCbCrToRgbFunction::GetName() const
{
    return YCbCrToRgbFunctionGenerator{}.GetName();
}

pp::IFunctionPtr pp::YCbCrToRgbFunctionGenerator::Make(IFunctionPtr fun)
{
    return std::make_unique<YCbCrToRgbFunction>(std::move(fun));
}

const std::string& pp::YCbCrToRgbFunctionGenerator::GetName() const
{
    static std::string name = "ycbcr-to-rgb";
    return name;
}
