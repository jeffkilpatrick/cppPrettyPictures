#include "pp/fun/NegateFunction.h"

using pp::NegateFunction;
using pp::NegateFunctionGenerator;

NegateFunction::NegateFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float NegateFunction::EvalSingle(float x, float y, float a) const
{
    return -1.f * a;
}

std::string NegateFunction::ToString() const
{
    return "(neg " + ArgString() + ")";
}

// --------------------------------------------------------------------

pp::IFunctionPtr NegateFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<NegateFunction>(std::move(arg));
}
