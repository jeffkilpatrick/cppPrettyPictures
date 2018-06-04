#include "pp/fun/DissolveFunction.h"

using pp::DissolveFunction;

DissolveFunction::DissolveFunction(IFunctionPtr fun0, IFunctionPtr fun1, IFunctionPtr fun2)
    : ITrinaryFunction(std::move(fun0), std::move(fun1), std::move(fun2))
    , m_truncate(nullptr)
{ }

float DissolveFunction::EvalSingle(float x, float y, float a0, float a1, float a2) const
{
    a2 = m_truncate.EvalSingle(x, y, a2);
    a2 = a2 < 0.f ? -1.f * a2 : a2;

    return a0 * a2 + a1 * (1.0 - a2);
}

const std::string& DissolveFunction::GetName() const
{
    static std::string name = "dissolve";
    return name;
}

pp::IFunctionPtr pp::DissolveFunctionGenerator::Make(IFunctionPtr fun0, IFunctionPtr fun1, IFunctionPtr fun2)
{
    return std::make_unique<pp::DissolveFunction>(std::move(fun0), std::move(fun1), std::move(fun2));
}