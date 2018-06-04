#include "pp/fun/IFunction.h"

#include <ostream>

using pp::IFunction;
using pp::INonaryFunction;
using pp::IUnaryFunction;
using pp::IBinaryFunction;
using pp::ITrinaryFunction;

IFunction::~IFunction() = default;

IFunction::IFunction() = default;

IFunction::IFunction(IFunctionPtr arg0)
{
    m_args.emplace_back(std::move(arg0));
}

IFunction::IFunction(IFunctionPtr arg0, IFunctionPtr arg1)
{
    m_args.emplace_back(std::move(arg0));
    m_args.emplace_back(std::move(arg1));
}

IFunction::IFunction(IFunctionPtr arg0, IFunctionPtr arg1, IFunctionPtr arg2)
{
    m_args.emplace_back(std::move(arg0));
    m_args.emplace_back(std::move(arg1));
    m_args.emplace_back(std::move(arg2));
}

std::string IFunction::ToString() const
{
    auto s = '(' + GetName();

    for (const auto& arg : m_args)
    {
        s += ' ' + arg->ToString();
    }

    s += ')';

    return s;
}

const pp::IFunctionPtrVec& IFunction::GetArgs() const
{
    return m_args;
}

// ----------------------------------------------------------
INonaryFunction::INonaryFunction() = default;

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

IUnaryFunction::IUnaryFunction(IFunctionPtr arg)
    : IFunction(std::move(arg))
{ }

pp::Color IUnaryFunction::Eval(float x, float y) const
{
    auto c = GetArgs().at(0)->Eval(x, y);
    c.C1 = EvalSingle(x, y, c.C1);
    c.C2 = EvalSingle(x, y, c.C2);
    c.C3 = EvalSingle(x, y, c.C3);

    // TODO-jrk: remove
    if (std::isnan(c.C1) || std::isnan(c.C2) || std::isnan(c.C3))
    {
        fprintf(stderr, "nan with %s\n", GetArgs().at(0)->ToString().c_str());
        std::exit(1);
    }

    return c;
}

// ----------------------------------------------------------

IBinaryFunction::IBinaryFunction(IFunctionPtr fun0, IFunctionPtr fun1)
    : IFunction(std::move(fun0), std::move(fun1))
{ }

pp::Color IBinaryFunction::Eval(float x, float y) const
{
    auto c0 = GetArgs().at(0)->Eval(x, y);
    auto c1 = GetArgs().at(1)->Eval(x, y);

    // TODO-jrk: remove
    if (std::isnan(c0.C1) || std::isnan(c0.C2) || std::isnan(c0.C3))
    {
        fprintf(stderr, "nan with %s\n", GetArgs().at(0)->ToString().c_str());
        std::exit(1);
    }

    if (std::isnan(c1.C1) || std::isnan(c1.C2) || std::isnan(c1.C3))
    {
        fprintf(stderr, "nan with %s\n", GetArgs().at(1)->ToString().c_str());
        std::exit(1);
    }

    c0.C1 = EvalSingle(x, y, c0.C1, c1.C1);
    c0.C2 = EvalSingle(x, y, c0.C2, c1.C2);
    c0.C3 = EvalSingle(x, y, c0.C3, c1.C3);

    return c0;
}

// ----------------------------------------------------------

ITrinaryFunction::ITrinaryFunction(IFunctionPtr fun0, IFunctionPtr fun1, IFunctionPtr fun2)
    : IFunction(std::move(fun0), std::move(fun1), std::move(fun2))
{ }

pp::Color ITrinaryFunction::Eval(float x, float y) const
{
    auto c0 = GetArgs().at(0)->Eval(x, y);
    auto c1 = GetArgs().at(1)->Eval(x, y);
    auto c2 = GetArgs().at(2)->Eval(x, y);

    // TODO-jrk: remove
    if (std::isnan(c0.C1) || std::isnan(c0.C2) || std::isnan(c0.C3))
    {
        fprintf(stderr, "nan with %s\n", GetArgs().at(0)->ToString().c_str());
        std::exit(1);
    }

    if (std::isnan(c1.C1) || std::isnan(c1.C2) || std::isnan(c1.C3))
    {
        fprintf(stderr, "nan with %s\n", GetArgs().at(1)->ToString().c_str());
        std::exit(1);
    }

    if (std::isnan(c2.C1) || std::isnan(c2.C2) || std::isnan(c2.C3))
    {
        fprintf(stderr, "nan with %s\n", GetArgs().at(2)->ToString().c_str());
        std::exit(1);
    }

    c0.C1 = EvalSingle(x, y, c0.C1, c1.C1, c2.C1);
    c0.C2 = EvalSingle(x, y, c0.C2, c1.C2, c2.C2);
    c0.C3 = EvalSingle(x, y, c0.C3, c1.C3, c2.C3);

    return c0;
}

// ----------------------------------------------------------

std::ostream& pp::operator<<(std::ostream& s, const IFunction& fun)
{
    s << fun.ToString();
    return s;
}
