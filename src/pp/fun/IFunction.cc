#include "pp/fun/IFunction.h"

using pp::IFunction;
using pp::INonaryFunction;
using pp::IUnaryFunction;
using pp::IBinaryFunction;
using pp::ITrinaryFunction;

IFunction::~IFunction() = default;

// ----------------------------------------------------------
#include <cmath> // TODO-jrk: remove
pp::Color INonaryFunction::Eval(float x, float y) const
{
    auto val = EvalSingle(x, y);
    // TODO-jrk: remove
    if (std::isnan(val))
    {
        fprintf(stderr, "nan with %s\n", ToString().c_str());
        std::exit(1);
    }
    return { val, val , val };
}

// ----------------------------------------------------------

IUnaryFunction::IUnaryFunction(IFunctionPtr fun)
    : m_fun(std::move(fun))
{ }

pp::Color IUnaryFunction::Eval(float x, float y) const
{
    auto c = m_fun->Eval(x, y);
    c.C1 = EvalSingle(x, y, c.C1);
    c.C2 = EvalSingle(x, y, c.C2);
    c.C3 = EvalSingle(x, y, c.C3);

    // TODO-jrk: remove
    if (std::isnan(c.C1) || std::isnan(c.C2) || std::isnan(c.C3))
    {
        fprintf(stderr, "nan with %s\n", m_fun->ToString().c_str());
        std::exit(1);
    }

    return c;
}

std::string IUnaryFunction::ArgString() const
{
    return m_fun->ToString();
}

// ----------------------------------------------------------

IBinaryFunction::IBinaryFunction(IFunctionPtr fun0, IFunctionPtr fun1)
    : m_fun0(std::move(fun0))
    , m_fun1(std::move(fun1))
{ }

pp::Color IBinaryFunction::Eval(float x, float y) const
{
    auto c0 = m_fun0->Eval(x, y);
    auto c1 = m_fun1->Eval(x, y);

    // TODO-jrk: remove
    if (std::isnan(c0.C1) || std::isnan(c0.C2) || std::isnan(c0.C3))
    {
        fprintf(stderr, "nan with %s\n", m_fun0->ToString().c_str());
        std::exit(1);
    }

    if (std::isnan(c1.C1) || std::isnan(c1.C2) || std::isnan(c1.C3))
    {
        fprintf(stderr, "nan with %s\n", m_fun1->ToString().c_str());
        std::exit(1);
    }

    c0.C1 = EvalSingle(x, y, c0.C1, c1.C1);
    c0.C2 = EvalSingle(x, y, c0.C2, c1.C2);
    c0.C3 = EvalSingle(x, y, c0.C3, c1.C3);

    return c0;
}

std::string IBinaryFunction::Arg0String() const
{
    return m_fun0->ToString();
}

std::string IBinaryFunction::Arg1String() const
{
    return m_fun1->ToString();
}

// ----------------------------------------------------------

ITrinaryFunction::ITrinaryFunction(IFunctionPtr fun0, IFunctionPtr fun1, IFunctionPtr fun2)
    : m_fun0(std::move(fun0))
    , m_fun1(std::move(fun1))
    , m_fun2(std::move(fun2))
{ }

pp::Color ITrinaryFunction::Eval(float x, float y) const
{
    auto c0 = m_fun0->Eval(x, y);
    auto c1 = m_fun1->Eval(x, y);
    auto c2 = m_fun2->Eval(x, y);

    // TODO-jrk: remove
    if (std::isnan(c0.C1) || std::isnan(c0.C2) || std::isnan(c0.C3))
    {
        fprintf(stderr, "nan with %s\n", m_fun0->ToString().c_str());
        std::exit(1);
    }

    if (std::isnan(c1.C1) || std::isnan(c1.C2) || std::isnan(c1.C3))
    {
        fprintf(stderr, "nan with %s\n", m_fun1->ToString().c_str());
        std::exit(1);
    }

    if (std::isnan(c2.C1) || std::isnan(c2.C2) || std::isnan(c2.C3))
    {
        fprintf(stderr, "nan with %s\n", m_fun2->ToString().c_str());
        std::exit(1);
    }

    c0.C1 = EvalSingle(x, y, c0.C1, c1.C1, c2.C1);
    c0.C2 = EvalSingle(x, y, c0.C2, c1.C2, c2.C2);
    c0.C3 = EvalSingle(x, y, c0.C3, c1.C3, c2.C3);

    return c0;
}

std::string ITrinaryFunction::Arg0String() const
{
    return m_fun0->ToString();
}

std::string ITrinaryFunction::Arg1String() const
{
    return m_fun1->ToString();
}

std::string ITrinaryFunction::Arg2String() const
{
    return m_fun2->ToString();
}

// ----------------------------------------------------------

std::ostream& pp::operator<<(std::ostream& s, const IFunction& fun)
{
    s << fun.ToString();
    return s;
}
