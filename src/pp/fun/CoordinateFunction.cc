#include "pp/fun/Arity.h"
#include "pp/fun/CoordinateFunction.h"

using pp::XFunction;
using pp::YFunction;
using pp::XFunctionGenerator;
using pp::YFunctionGenerator;

float XFunction::EvalSingle(float x, float y) const
{
    return x;
}

const std::string& XFunction::GetName() const
{
    static std::string name = "x";
    return name;
}

pp::IFunctionPtr XFunctionGenerator::Make()
{
    return std::make_unique<XFunction>();
}

// --------------------------------------------------------------------

float YFunction::EvalSingle(float x, float y) const
{
    return y;
}

const std::string& YFunction::GetName() const
{
    static std::string name = "y";
    return name;
}

pp::IFunctionPtr YFunctionGenerator::Make()
{
    return std::make_unique<YFunction>();
}
