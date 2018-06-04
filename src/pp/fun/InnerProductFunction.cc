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

const std::string& InnerProductFunction::GetName() const
{
    static std::string name = "inner-product";
    return name;
}

pp::IFunctionPtr InnerProductFunctionGenerator::Make(IFunctionPtr fun0, IFunctionPtr fun1)
{
    return std::make_unique<InnerProductFunction>(std::move(fun0), std::move(fun1));
}