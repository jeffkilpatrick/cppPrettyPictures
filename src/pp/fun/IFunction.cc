#include "pp/fun/IFunction.h"

using pp::IFunction;
using pp::INonaryFunction;
using pp::IUnaryFunction;
using pp::IBinaryFunction;
using pp::ITrinaryFunction;

IFunction::~IFunction() = default;

IFunction::IFunction() = default;

IFunction::IFunction(IFunctionPtr arg0)
    : m_buffers(1, std::vector<Color>{})
{
    m_args.emplace_back(std::move(arg0));
}

IFunction::IFunction(IFunctionPtr arg0, IFunctionPtr arg1)
    : m_buffers(2, std::vector<Color>{})
{
    m_args.emplace_back(std::move(arg0));
    m_args.emplace_back(std::move(arg1));
}

IFunction::IFunction(IFunctionPtr arg0, IFunctionPtr arg1, IFunctionPtr arg2)
    : m_buffers(3, std::vector<Color>{})
{
    m_args.emplace_back(std::move(arg0));
    m_args.emplace_back(std::move(arg1));
    m_args.emplace_back(std::move(arg2));
}

const pp::IFunctionPtrVec& IFunction::GetArgs() const
{
    return m_args;
}

void IFunction::EvalRow(const std::vector<float>& xs, float y, Color* out) const
{
    for (auto x : xs)
    {
        *out = Eval(x, y);
        ++out;
    }
}

// ----------------------------------------------------------
INonaryFunction::INonaryFunction() = default;

pp::Color INonaryFunction::Eval(float x, float y) const
{
    auto val = EvalSingle(x, y);

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

    return c;
}

void IUnaryFunction::EvalRow(const std::vector<float>& xs, float y, Color* out) const
{
    m_buffers.at(0).resize(xs.size(), Color{0.f});

    GetArgs().at(0)->EvalRow(xs, y, m_buffers.at(0).data());

    for (size_t i = 0; i < xs.size(); ++i)
    {
        *out = Color{
            EvalSingle(xs[i], y, m_buffers.at(0)[i].C1),
            EvalSingle(xs[i], y, m_buffers.at(0)[i].C2),
            EvalSingle(xs[i], y, m_buffers.at(0)[i].C3)
        };
        ++out;
    }
}

// ----------------------------------------------------------

IBinaryFunction::IBinaryFunction(IFunctionPtr fun0, IFunctionPtr fun1)
    : IFunction(std::move(fun0), std::move(fun1))
{ }

pp::Color IBinaryFunction::Eval(float x, float y) const
{
    auto c0 = GetArgs().at(0)->Eval(x, y);
    auto c1 = GetArgs().at(1)->Eval(x, y);

    c0.C1 = EvalSingle(x, y, c0.C1, c1.C1);
    c0.C2 = EvalSingle(x, y, c0.C2, c1.C2);
    c0.C3 = EvalSingle(x, y, c0.C3, c1.C3);

    return c0;
}

void IBinaryFunction::EvalRow(const std::vector<float>& xs, float y, Color* out) const
{
    m_buffers.at(0).resize(xs.size(), Color{0.f});
    m_buffers.at(1).resize(xs.size(), Color{0.f});

    GetArgs().at(0)->EvalRow(xs, y, m_buffers.at(0).data());
    GetArgs().at(1)->EvalRow(xs, y, m_buffers.at(1).data());

    for (size_t i = 0; i < xs.size(); ++i)
    {
        *out = Color{
            EvalSingle(xs[i], y, m_buffers.at(0)[i].C1, m_buffers.at(1)[i].C1),
            EvalSingle(xs[i], y, m_buffers.at(0)[i].C2, m_buffers.at(1)[i].C2),
            EvalSingle(xs[i], y, m_buffers.at(0)[i].C3, m_buffers.at(1)[i].C3)
        };
        ++out;
    }
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

    c0.C1 = EvalSingle(x, y, c0.C1, c1.C1, c2.C1);
    c0.C2 = EvalSingle(x, y, c0.C2, c1.C2, c2.C2);
    c0.C3 = EvalSingle(x, y, c0.C3, c1.C3, c2.C3);

    return c0;
}

void ITrinaryFunction::EvalRow(const std::vector<float>& xs, float y, Color* out) const
{
    m_buffers.at(0).resize(xs.size(), Color{0.f});
    m_buffers.at(1).resize(xs.size(), Color{0.f});
    m_buffers.at(2).resize(xs.size(), Color{0.f});

    GetArgs().at(0)->EvalRow(xs, y, m_buffers.at(0).data());
    GetArgs().at(1)->EvalRow(xs, y, m_buffers.at(1).data());
    GetArgs().at(2)->EvalRow(xs, y, m_buffers.at(2).data());

    for (size_t i = 0; i < xs.size(); ++i)
    {
        *out = Color{
            EvalSingle(xs[i], y, m_buffers.at(0)[i].C1, m_buffers.at(1)[i].C1, m_buffers.at(2)[i].C1),
            EvalSingle(xs[i], y, m_buffers.at(0)[i].C2, m_buffers.at(1)[i].C2, m_buffers.at(2)[i].C2),
            EvalSingle(xs[i], y, m_buffers.at(0)[i].C3, m_buffers.at(1)[i].C3, m_buffers.at(2)[i].C3)
        };
        ++out;
    }
}
