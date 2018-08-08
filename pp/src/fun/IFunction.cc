#include "pp/fun/IFunction.h"
#include "pp/utility/BufferPool.h"

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

const pp::IFunctionPtrVec& IFunction::GetArgs() const
{
    return m_args;
}

bool IFunction::Equals(const IFunction& other) const
{
    if (typeid(*this) != typeid(other))
    {
        return false;
    }

    for (size_t i = 0; i < GetArgs().size(); ++i)
    {
        if (!GetArgs().at(i)->Equals(*other.GetArgs().at(i)))
        {
            return false;
        }
    }

    return true;
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
    auto buf = BufferPool::Instance().Get();
    buf->resize(xs.size(), Color{0.f});

    GetArgs().at(0)->EvalRow(xs, y, buf->data());

    for (size_t i = 0; i < xs.size(); ++i)
    {
        *out = Color{
            EvalSingle(xs[i], y, (*buf)[i].C1),
            EvalSingle(xs[i], y, (*buf)[i].C2),
            EvalSingle(xs[i], y, (*buf)[i].C3)
        };
        ++out;
    }

    BufferPool::Instance().Return(std::move(buf));
}

// ----------------------------------------------------------

IBinaryFunction::IBinaryFunction(IFunctionPtr fun0, IFunctionPtr fun1)
    : IFunction(std::move(fun0), std::move(fun1))
{ }

void IBinaryFunction::EvalRow(const std::vector<float>& xs, float y, Color* out) const
{
    auto buf0 = BufferPool::Instance().Get();
    auto buf1 = BufferPool::Instance().Get();

    buf0->resize(xs.size(), Color{0.f});
    buf1->resize(xs.size(), Color{0.f});

    GetArgs().at(0)->EvalRow(xs, y, buf0->data());
    GetArgs().at(1)->EvalRow(xs, y, buf1->data());

    for (size_t i = 0; i < xs.size(); ++i)
    {
        *out = Color{
            EvalSingle(xs[i], y, (*buf0)[i].C1, (*buf1)[i].C1),
            EvalSingle(xs[i], y, (*buf0)[i].C2, (*buf1)[i].C2),
            EvalSingle(xs[i], y, (*buf0)[i].C3, (*buf1)[i].C3)
        };
        ++out;
    }

    BufferPool::Instance().Return(std::move(buf1));
    BufferPool::Instance().Return(std::move(buf0));
}

// ----------------------------------------------------------

ITrinaryFunction::ITrinaryFunction(IFunctionPtr fun0, IFunctionPtr fun1, IFunctionPtr fun2)
    : IFunction(std::move(fun0), std::move(fun1), std::move(fun2))
{ }

void ITrinaryFunction::EvalRow(const std::vector<float>& xs, float y, Color* out) const
{
    auto buf0 = BufferPool::Instance().Get();
    auto buf1 = BufferPool::Instance().Get();
    auto buf2 = BufferPool::Instance().Get();

    buf0->resize(xs.size(), Color{0.f});
    buf1->resize(xs.size(), Color{0.f});
    buf2->resize(xs.size(), Color{0.f});

    GetArgs().at(0)->EvalRow(xs, y, buf0->data());
    GetArgs().at(1)->EvalRow(xs, y, buf1->data());
    GetArgs().at(2)->EvalRow(xs, y, buf2->data());

    for (size_t i = 0; i < xs.size(); ++i)
    {
        *out = Color{
            EvalSingle(xs[i], y, (*buf0)[i].C1, (*buf1)[i].C1, (*buf2)[i].C1),
            EvalSingle(xs[i], y, (*buf0)[i].C2, (*buf1)[i].C2, (*buf2)[i].C2),
            EvalSingle(xs[i], y, (*buf0)[i].C3, (*buf1)[i].C3, (*buf2)[i].C3)
        };
        ++out;
    }

    BufferPool::Instance().Return(std::move(buf2));
    BufferPool::Instance().Return(std::move(buf1));
    BufferPool::Instance().Return(std::move(buf0));
}
