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

std::string AbsFunction::ToString() const
{
    return "(abs " + GetArgs().at(0)->ToString() + ")";
}

pp::IFunctionPtr AbsFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<AbsFunction>(std::move(arg));
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

std::string ClipFunction::ToString() const
{
    return "(clip " + GetArgs().at(0)->ToString() + ")";
}

pp::IFunctionPtr ClipFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<ClipFunction>(std::move(arg));
}

// --------------------------------------------------------------------

RoundDownFunction::RoundDownFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float RoundDownFunction::EvalSingle(float x, float y, float a) const
{
    return std::floor(a);
}

std::string RoundDownFunction::ToString() const
{
    return "(floor " + GetArgs().at(0)->ToString() + ")";
}

pp::IFunctionPtr RoundDownFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<RoundDownFunction>(std::move(arg));
}

// --------------------------------------------------------------------

RoundUpFunction::RoundUpFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float RoundUpFunction::EvalSingle(float x, float y, float a) const
{
    return std::ceil(a);
}

std::string RoundUpFunction::ToString() const
{
    return "(ceil " + GetArgs().at(0)->ToString() + ")";
}

pp::IFunctionPtr RoundUpFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<RoundUpFunction>(std::move(arg));
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

std::string WrapFunction::ToString() const
{
    return "(wrap " + GetArgs().at(0)->ToString() + ")";
}

pp::IFunctionPtr WrapFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<WrapFunction>(std::move(arg));
}

