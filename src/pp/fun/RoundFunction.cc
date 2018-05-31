#include "pp/fun/Arity.h"
#include "pp/fun/RoundFunction.h"

using pp::RoundDownFunction;
using pp::RoundDownFunctionGenerator;
using pp::RoundUpFunction;
using pp::RoundUpFunctionGenerator;

RoundDownFunction::RoundDownFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float RoundDownFunction::Eval(float x, float y) const
{
    return std::floor(EvalArg(x, y));
}

pp::Arity RoundDownFunctionGenerator::GetArity() const
{
    return Arity::Unary;
}

pp::IFunctionPtr RoundDownFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<RoundDownFunction>(std::move(arg));
}

// --------------------------------------------------------------------

RoundUpFunction::RoundUpFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float RoundUpFunction::Eval(float x, float y) const
{
    return std::ceil(EvalArg(x, y));
}

pp::Arity RoundUpFunctionGenerator::GetArity() const
{
    return Arity::Unary;
}

pp::IFunctionPtr RoundUpFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<RoundUpFunction>(std::move(arg));
}

