#include "pp/fun/Arity.h"
#include "pp/fun/NegateFunction.h"

using pp::NegateFunction;
using pp::NegateFunctionGenerator;

NegateFunction::NegateFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float NegateFunction::Eval(float x, float y) const
{
    return -1.0f * EvalArg(x, y);
}

// --------------------------------------------------------------------

pp::Arity NegateFunctionGenerator::GetArity() const
{
    return Arity::Unary;
}

pp::IFunctionPtr NegateFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<NegateFunction>(std::move(arg));
}
