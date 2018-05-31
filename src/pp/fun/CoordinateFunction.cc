#include "pp/fun/Arity.h"
#include "pp/fun/CoordinateFunction.h"

using pp::XFunction;
using pp::YFunction;
using pp::XFunctionGenerator;
using pp::YFunctionGenerator;

float XFunction::Eval(float x, float y) const
{
    return x;
}

pp::Arity XFunctionGenerator::GetArity() const
{
    return Arity::Nonary;
}

pp::IFunctionPtr XFunctionGenerator::Make()
{
    return std::make_unique<XFunction>();
}

// --------------------------------------------------------------------

float YFunction::Eval(float x, float y) const
{
    return y;
}

pp::Arity YFunctionGenerator::GetArity() const
{
    return Arity::Nonary;
}

pp::IFunctionPtr YFunctionGenerator::Make()
{
    return std::make_unique<YFunction>();
}
