#include "pp/fun/Arity.h"
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

float AbsFunction::Eval(float x, float y) const
{
    return std::abs(EvalArg(x, y));
}

std::string AbsFunction::ToString() const
{
    return "(abs " + ArgString() + ")";
}

pp::Arity AbsFunctionGenerator::GetArity() const
{
    return Arity::Unary;
}

pp::IFunctionPtr AbsFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<AbsFunction>(std::move(arg));
}

// --------------------------------------------------------------------

ClipFunction::ClipFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float ClipFunction::Eval(float x, float y) const
{
    auto arg = EvalArg(x, y);
    arg = std::min(arg, 1.0f);
    arg = std::max(arg, -1.0f);
    return arg;
}

std::string ClipFunction::ToString() const
{
    return "(clip " + ArgString() + ")";
}

pp::Arity ClipFunctionGenerator::GetArity() const
{
    return Arity::Unary;
}

pp::IFunctionPtr ClipFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<ClipFunction>(std::move(arg));
}

// --------------------------------------------------------------------

RoundDownFunction::RoundDownFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float RoundDownFunction::Eval(float x, float y) const
{
    return std::floor(EvalArg(x, y));
}

std::string RoundDownFunction::ToString() const
{
    return "(floor " + ArgString() + ")";
}

pp::Arity RoundDownFunctionGenerator::GetArity() const
{
    return Arity::Unary;
}

pp::IFunctionPtr RoundDownFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<RoundDownFunction>(std::move(arg));
}

// --------------------------------------------------------------------

RoundUpFunction::RoundUpFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float RoundUpFunction::Eval(float x, float y) const
{
    return std::ceil(EvalArg(x, y));
}

std::string RoundUpFunction::ToString() const
{
    return "(ceil " + ArgString() + ")";
}

pp::Arity RoundUpFunctionGenerator::GetArity() const
{
    return Arity::Unary;
}

pp::IFunctionPtr RoundUpFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<RoundUpFunction>(std::move(arg));
}

// --------------------------------------------------------------------

WrapFunction::WrapFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float WrapFunction::Eval(float x, float y) const
{
    auto arg = EvalArg(x, y);
    auto n = std::round(arg / 2.f);
    return arg - (2.f * n);
}

std::string WrapFunction::ToString() const
{
    return "(wrap " + ArgString() + ")";
}

pp::Arity WrapFunctionGenerator::GetArity() const
{
    return Arity::Unary;
}

pp::IFunctionPtr WrapFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<WrapFunction>(std::move(arg));
}

