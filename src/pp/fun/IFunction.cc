#include "pp/fun/IFunction.h"

using pp::IFunction;
using pp::IUnaryFunction;
using pp::IBinaryFunction;
using pp::ITrinaryFunction;

IFunction::~IFunction() = default;

IUnaryFunction::IUnaryFunction(IFunctionPtr fun)
    : m_fun(std::move(fun))
{ }

float IUnaryFunction::EvalArg(float x, float y) const
{
    return m_fun->Eval(x, y);
}

std::string IUnaryFunction::ArgString() const
{
    return m_fun->ToString();
}

std::ostream& pp::operator<<(std::ostream& s, const IFunction& fun)
{
    s << fun.ToString();
    return s;
}
