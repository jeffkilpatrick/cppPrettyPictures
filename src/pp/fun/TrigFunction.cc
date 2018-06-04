#include "pp/fun/TrigFunction.h"

using pp::AtanFunction;
using pp::AtanFunctionGenerator;
using pp::CosFunction;
using pp::CosFunctionGenerator;
using pp::SinFunction;
using pp::SinFunctionGenerator;

AtanFunction::AtanFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float AtanFunction::EvalSingle(float x, float y, float a) const
{
    return std::atan(a);
}

const std::string& AtanFunction::GetName() const
{
    static std::string name = "atan";
    return name;
}

pp::IFunctionPtr AtanFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<AtanFunction>(std::move(arg));
}

// --------------------------------------------------------------------

CosFunction::CosFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float CosFunction::EvalSingle(float x, float y, float a) const
{
    return std::cos(a);
}

const std::string& CosFunction::GetName() const
{
    static std::string name = "cos";
    return name;
}

pp::IFunctionPtr CosFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<CosFunction>(std::move(arg));
}

// --------------------------------------------------------------------

SinFunction::SinFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float SinFunction::EvalSingle(float x, float y, float a) const
{
    return std::sin(a);
}

const std::string& SinFunction::GetName() const
{
    static std::string name = "sin";
    return name;
}

pp::IFunctionPtr SinFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<SinFunction>(std::move(arg));
}
