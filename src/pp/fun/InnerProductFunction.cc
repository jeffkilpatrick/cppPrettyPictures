#include "pp/fun/InnerProductFunction.h"

using pp::InnerProductFunction;
using pp::InnerProductFunctionGenerator;

InnerProductFunction::InnerProductFunction(IFunctionPtr fun0, IFunctionPtr fun1)
    : m_fun0(std::move(fun0))
    , m_fun1(std::move(fun1))
{ }

pp::Color InnerProductFunction::Eval(float x, float y) const
{
    auto a = m_fun0->Eval(x, y);
    auto b = m_fun1->Eval(x, y);

    auto ip = a.C1 * b.C1
        + a.C2 * b.C2
        + a.C3 * b.C3;

    return Color{ ip };
}

std::string InnerProductFunction::ToString() const
{
    return "(inner-product " + m_fun0->ToString() + " " + m_fun1 ->ToString() + ")";
}

pp::IFunctionPtr InnerProductFunctionGenerator::Make(IFunctionPtr fun0, IFunctionPtr fun1)
{
    return std::make_unique<InnerProductFunction>(std::move(fun0), std::move(fun1));
}