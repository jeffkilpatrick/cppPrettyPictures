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

const std::string& AddFunction::GetName() const
{
    return AddFunctionGenerator{}.GetName();
}

pp::IFunctionPtr AddFunctionGenerator::Make(IFunctionPtr arg0, IFunctionPtr arg1)
{
    return std::make_unique<AddFunction>(std::move(arg0), std::move(arg1));
}

const std::string& AddFunctionGenerator::GetName() const
{
    static std::string name = "add";
    return name;    
}

// --------------------------------------------------------------------

SubtractFunction::SubtractFunction(IFunctionPtr arg0, IFunctionPtr arg1)
    : IBinaryFunction(std::move(arg0), std::move(arg1))
{ }

float SubtractFunction::EvalSingle(float x, float y, float a0, float a1) const
{
    return a0 - a1;
}

const std::string& SubtractFunction::GetName() const
{
    return SubtractFunctionGenerator{}.GetName();
}

pp::IFunctionPtr SubtractFunctionGenerator::Make(IFunctionPtr arg0, IFunctionPtr arg1)
{
    return std::make_unique<SubtractFunction>(std::move(arg0), std::move(arg1));
}

const std::string& SubtractFunctionGenerator::GetName() const
{
    static std::string name = "sub";
    return name;
}

// --------------------------------------------------------------------

MultiplyFunction::MultiplyFunction(IFunctionPtr arg0, IFunctionPtr arg1)
    : IBinaryFunction(std::move(arg0), std::move(arg1))
{ }

float MultiplyFunction::EvalSingle(float x, float y, float a0, float a1) const
{
    return a0 * a1;
}

const std::string& MultiplyFunction::GetName() const
{
    return MultiplyFunctionGenerator{}.GetName();
}

pp::IFunctionPtr MultiplyFunctionGenerator::Make(IFunctionPtr arg0, IFunctionPtr arg1)
{
    return std::make_unique<MultiplyFunction>(std::move(arg0), std::move(arg1));
}

const std::string& MultiplyFunctionGenerator::GetName() const
{
    static std::string name = "mul";
    return name;
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

const std::string& DivideFunction::GetName() const
{
    return DivideFunctionGenerator{}.GetName();
}

pp::IFunctionPtr DivideFunctionGenerator::Make(IFunctionPtr arg0, IFunctionPtr arg1)
{
    return std::make_unique<DivideFunction>(std::move(arg0), std::move(arg1));
}

const std::string& DivideFunctionGenerator::GetName() const
{
    static std::string name = "div";
    return name;
}
