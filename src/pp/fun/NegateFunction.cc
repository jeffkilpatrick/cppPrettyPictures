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

const std::string& NegateFunction::GetName() const
{
    static std::string name = "neg";
    return name;
}

// --------------------------------------------------------------------

pp::IFunctionPtr NegateFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<NegateFunction>(std::move(arg));
}
