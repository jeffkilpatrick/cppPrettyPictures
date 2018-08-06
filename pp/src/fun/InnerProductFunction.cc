#include "pp/fun/InnerProductFunction.h"

using pp::InnerProductFunction;

InnerProductFunction::InnerProductFunction(IFunctionPtr fun0, IFunctionPtr fun1)
    : IFunction(std::move(fun0), std::move(fun1))
{ }

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
