#include "pp/fun/IFunction.h"

using pp::IFunction;
using pp::INonaryFunction;
using pp::IUnaryFunction;
using pp::IBinaryFunction;
using pp::ITrinaryFunction;

IFunction::~IFunction() = default;

pp::Color INonaryFunction::Eval(float x, float y) const
{
    auto val = EvalSingle(x, y);
    return { val, val , val };
}

IUnaryFunction::IUnaryFunction(IFunctionPtr fun)
    : m_fun(std::move(fun))
{ }

pp::Color IUnaryFunction::Eval(float x, float y) const
{
    auto c = m_fun->Eval(x, y);
    c.C1 = EvalSingle(x, y, c.C1);
    c.C2 = EvalSingle(x, y, c.C2);
    c.C3 = EvalSingle(x, y, c.C3);
    return c;
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
