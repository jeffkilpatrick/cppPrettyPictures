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

pp::Color IFunction::Eval(float x, float y) const
{
    Color c{0.f};
    EvalRow({x}, y, &c);
    return c;
}

// ----------------------------------------------------------
INonaryFunction::INonaryFunction() = default;

// ----------------------------------------------------------

IUnaryFunction::IUnaryFunction(IFunctionPtr arg)
    : IFunction(std::move(arg))
{ }

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
