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

float AtanFunction::Eval(float x, float y) const
{
    return std::atan(EvalArg(x, y));
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

float CosFunction::Eval(float x, float y) const
{
    return std::cos(EvalArg(x, y));
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

float SinFunction::Eval(float x, float y) const
{
    return std::sin(EvalArg(x, y));
}

pp::Arity SinFunctionGenerator::GetArity() const
{
    return Arity::Unary;
}

pp::IFunctionPtr SinFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<SinFunction>(std::move(arg));
}
