#include "pp/fun/ArithmeticFunction.h"

#include <cmath>

using pp::AddFunction;
using pp::AddFunctionGenerator;
using pp::DivideFunction;
using pp::DivideFunctionGenerator;
using pp::MultiplyFunction;
using pp::MultiplyFunctionGenerator;
using pp::SubtractFunction;
using pp::SubtractFunctionGenerator;

AddFunction::AddFunction(IFunctionPtr arg0, IFunctionPtr arg1)
    : IBinaryFunction(std::move(arg0), std::move(arg1))
{ }

float AddFunction::EvalSingle(float x, float y, float a0, float a1) const
{
    return a0 + a1;
}

std::string AddFunction::ToString() const
{
    return "(add " + GetArgs().at(0)->ToString() + " " + GetArgs().at(1)->ToString() + ")";
}

pp::IFunctionPtr AddFunctionGenerator::Make(IFunctionPtr arg0, IFunctionPtr arg1)
{
    return std::make_unique<AddFunction>(std::move(arg0), std::move(arg1));
}

// --------------------------------------------------------------------

SubtractFunction::SubtractFunction(IFunctionPtr arg0, IFunctionPtr arg1)
    : IBinaryFunction(std::move(arg0), std::move(arg1))
{ }

float SubtractFunction::EvalSingle(float x, float y, float a0, float a1) const
{
    return a0 - a1;
}

std::string SubtractFunction::ToString() const
{
    return "(sub " + GetArgs().at(0)->ToString() + " " + GetArgs().at(1)->ToString() + ")";
}

pp::IFunctionPtr SubtractFunctionGenerator::Make(IFunctionPtr arg0, IFunctionPtr arg1)
{
    return std::make_unique<SubtractFunction>(std::move(arg0), std::move(arg1));
}

// --------------------------------------------------------------------

MultiplyFunction::MultiplyFunction(IFunctionPtr arg0, IFunctionPtr arg1)
    : IBinaryFunction(std::move(arg0), std::move(arg1))
{ }

float MultiplyFunction::EvalSingle(float x, float y, float a0, float a1) const
{
    return a0 * a1;
}

std::string MultiplyFunction::ToString() const
{
    return "(mul " + GetArgs().at(0)->ToString() + " " + GetArgs().at(1)->ToString() + ")";
}

pp::IFunctionPtr MultiplyFunctionGenerator::Make(IFunctionPtr arg0, IFunctionPtr arg1)
{
    return std::make_unique<MultiplyFunction>(std::move(arg0), std::move(arg1));
}

// --------------------------------------------------------------------

DivideFunction::DivideFunction(IFunctionPtr arg0, IFunctionPtr arg1)
    : IBinaryFunction(std::move(arg0), std::move(arg1))
{ }

float DivideFunction::EvalSingle(float x, float y, float a0, float a1) const
{
    if (std::abs(a1) < 1e-3f)
    {
        a1 = std::copysign(1e-3f, a1);
    }

    return a0 / a1;
}

std::string DivideFunction::ToString() const
{
    return "(div " + GetArgs().at(0)->ToString() + " " + GetArgs().at(1)->ToString() + ")";
}

pp::IFunctionPtr DivideFunctionGenerator::Make(IFunctionPtr arg0, IFunctionPtr arg1)
{
    return std::make_unique<DivideFunction>(std::move(arg0), std::move(arg1));
}
