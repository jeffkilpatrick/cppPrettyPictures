#include "pp/fun/Arity.h"
#include "pp/fun/ConstantFunction.h"

#include <sstream>

using pp::ConstantFunction;
using pp::ConstantFunctionGenerator;

static std::string ConstantString(const pp::Color& constant)
{
    std::ostringstream str;
    str << constant;
    return str.str();
}

ConstantFunction::ConstantFunction(Color constant)
    : IFunction()
    , m_constant(constant)
    , m_constantStr(ConstantString(constant))
{
    // TODO-jrk: validate range of constant
}

pp::Color ConstantFunction::Eval(float x, float y) const
{
    return m_constant;
}

const std::string& ConstantFunction::GetName() const
{
    return m_constantStr;
}

// --------------------------------------------------------------------

ConstantFunctionGenerator::ConstantFunctionGenerator()
    : m_gen{std::random_device{}()}
{ }

pp::IFunctionPtr ConstantFunctionGenerator::Make()
{
    // Deviation from spec: this is [-1, 1) instead of [-1, 1].
    std::uniform_real_distribution<float> dist(-1.f, 1.f);

    auto c1 = dist(m_gen);
    auto c2 = dist(m_gen);
    auto c3 = dist(m_gen);

    return std::make_unique<ConstantFunction>(Color{c1, c2, c3});
}

const std::string& ConstantFunctionGenerator::GetName() const
{
    static std::string name = "const";
    return name;
}

