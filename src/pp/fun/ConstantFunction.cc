#include "pp/fun/Arity.h"
#include "pp/fun/ConstantFunction.h"

using pp::ConstantFunction;
using pp::ConstantFunctionGenerator;

ConstantFunction::ConstantFunction(float constant)
    : m_constant(constant)
{
    // TODO-jrk: validate range of constant
}

float ConstantFunction::Eval(float x, float y) const
{
    return m_constant;
}

// --------------------------------------------------------------------

ConstantFunctionGenerator::ConstantFunctionGenerator()
    : m_gen{std::random_device{}()}
{ }

pp::Arity ConstantFunctionGenerator::GetArity() const
{
    return Arity::Nonary;
}

pp::IFunctionPtr ConstantFunctionGenerator::Make()
{
    // Deviation from spec: this is [-1, 1) instead of [-1, 1].
    std::uniform_real_distribution<float> dist(-1.f, 1.f);

    return std::make_unique<ConstantFunction>(dist(m_gen));
}
