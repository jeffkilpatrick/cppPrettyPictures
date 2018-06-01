#include "pp/fun/Arity.h"
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

std::string AtanFunction::ToString() const
{
    return "(atan " + ArgString() + ")";
}

pp::Arity AtanFunctionGenerator::GetArity() const
{
    return Arity::Unary;
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

std::string CosFunction::ToString() const
{
    return "(cos " + ArgString() + ")";
}

pp::Arity CosFunctionGenerator::GetArity() const
{
    return Arity::Unary;
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

std::string SinFunction::ToString() const
{
    return "(sin " + ArgString() + ")";
}

pp::Arity SinFunctionGenerator::GetArity() const
{
    return Arity::Unary;
}

pp::IFunctionPtr SinFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<SinFunction>(std::move(arg));
}
