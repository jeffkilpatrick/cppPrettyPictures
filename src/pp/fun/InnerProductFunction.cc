#include "pp/fun/InnerProductFunction.h"

using pp::InnerProductFunction;
using pp::InnerProductFunctionGenerator;

InnerProductFunction::InnerProductFunction(IFunctionPtr fun0, IFunctionPtr fun1)
    : IFunction(std::move(fun0), std::move(fun1))
{ }

pp::Color InnerProductFunction::Eval(float x, float y) const
{
    auto a = GetArgs().at(0)->Eval(x, y);
    auto b = GetArgs().at(1)->Eval(x, y);

    auto ip = a.C1 * b.C1
        + a.C2 * b.C2
        + a.C3 * b.C3;

    return Color{ ip };
}

void InnerProductFunction::EvalRow(const std::vector<float>& xs, float y, Color* out) const
{
    m_buffers.at(0).resize(xs.size(), Color{0.f});
    m_buffers.at(1).resize(xs.size(), Color{0.f});

    GetArgs().at(0)->EvalRow(xs, y, m_buffers.at(0).data());
    GetArgs().at(1)->EvalRow(xs, y, m_buffers.at(1).data());

    for (size_t i = 0; i < xs.size(); ++i)
    {
        *out = Color{
            m_buffers.at(0)[i].C1 * m_buffers.at(1)[i].C1
          + m_buffers.at(0)[i].C2 * m_buffers.at(1)[i].C2
          + m_buffers.at(0)[i].C3 * m_buffers.at(1)[i].C3
        };
        ++out;
    }
}

const std::string& InnerProductFunction::GetName() const
{
    return InnerProductFunctionGenerator{}.GetName();
}

pp::IFunctionPtr InnerProductFunctionGenerator::Make(IFunctionPtr fun0, IFunctionPtr fun1)
{
    return std::make_unique<InnerProductFunction>(std::move(fun0), std::move(fun1));
}

const std::string& InnerProductFunctionGenerator::GetName() const
{
    static std::string name = "inner-product";
    return name;
}
