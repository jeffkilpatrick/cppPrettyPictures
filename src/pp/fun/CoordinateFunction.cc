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
    return XFunctionGenerator{}.GetName();
}

pp::IFunctionPtr XFunctionGenerator::Make()
{
    return std::make_unique<XFunction>();
}

const std::string& XFunctionGenerator::GetName() const
{
    static std::string name = "x";
    return name;
}

// --------------------------------------------------------------------

float YFunction::EvalSingle(float x, float y) const
{
    return y;
}

const std::string& YFunction::GetName() const
{
    return YFunctionGenerator{}.GetName();
}

pp::IFunctionPtr YFunctionGenerator::Make()
{
    return std::make_unique<YFunction>();
}

const std::string& YFunctionGenerator::GetName() const
{
    static std::string name = "y";
    return name;
}
