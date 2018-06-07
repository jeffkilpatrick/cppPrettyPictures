#include "pp/fun/RoundFunction.h"

using pp::AbsFunction;
using pp::AbsFunctionGenerator;
using pp::ClipFunction;
using pp::ClipFunctionGenerator;
using pp::RoundDownFunction;
using pp::RoundDownFunctionGenerator;
using pp::RoundUpFunction;
using pp::RoundUpFunctionGenerator;
using pp::WrapFunction;
using pp::WrapFunctionGenerator;

AbsFunction::AbsFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float AbsFunction::EvalSingle(float x, float y, float a) const
{
    return std::abs(a);
}

const std::string& AbsFunction::GetName() const
{
    return AbsFunctionGenerator{}.GetName();
}

pp::IFunctionPtr AbsFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<AbsFunction>(std::move(arg));
}

const std::string& AbsFunctionGenerator::GetName() const
{
    static std::string name = "abs";
    return name;
}

// --------------------------------------------------------------------

ClipFunction::ClipFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float ClipFunction::EvalSingle(float x, float y, float a) const
{
    a = std::min(a, 1.0f);
    a = std::max(a, -1.0f);
    return a;
}

const std::string& ClipFunction::GetName() const
{
    return ClipFunctionGenerator{}.GetName();
}

pp::IFunctionPtr ClipFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<ClipFunction>(std::move(arg));
}

const std::string& ClipFunctionGenerator::GetName() const
{
    static std::string name = "clip";
    return name;
}

// --------------------------------------------------------------------

RoundDownFunction::RoundDownFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float RoundDownFunction::EvalSingle(float x, float y, float a) const
{
    return std::floor(a);
}

const std::string& RoundDownFunction::GetName() const
{
    return RoundDownFunctionGenerator{}.GetName();
}

pp::IFunctionPtr RoundDownFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<RoundDownFunction>(std::move(arg));
}

const std::string& RoundDownFunctionGenerator::GetName() const
{
    static std::string name = "floor";
    return name;
}

// --------------------------------------------------------------------

RoundUpFunction::RoundUpFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float RoundUpFunction::EvalSingle(float x, float y, float a) const
{
    return std::ceil(a);
}

const std::string& RoundUpFunction::GetName() const
{
    return RoundUpFunctionGenerator{}.GetName();
}

pp::IFunctionPtr RoundUpFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<RoundUpFunction>(std::move(arg));
}

const std::string& RoundUpFunctionGenerator::GetName() const
{
    static std::string name = "ceil";
    return name;
}

// --------------------------------------------------------------------

WrapFunction::WrapFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float WrapFunction::EvalSingle(float x, float y, float a) const
{
    auto n = std::round(a / 2.f);
    return a - (2.f * n);
}

const std::string& WrapFunction::GetName() const
{
    return WrapFunctionGenerator{}.GetName();
}

pp::IFunctionPtr WrapFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<WrapFunction>(std::move(arg));
}

const std::string& WrapFunctionGenerator::GetName() const
{
    static std::string name = "wrap";
    return name;
}
