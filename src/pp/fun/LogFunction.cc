#include "pp/fun/Arity.h"
#include "pp/fun/LogFunction.h"

using pp::ExpFunction;
using pp::ExpFunctionGenerator;
using pp::LogFunction;
using pp::LogFunctionGenerator;

ExpFunction::ExpFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float ExpFunction::Eval(float x, float y) const
{
    return std::exp(EvalArg(x, y));
}

std::string ExpFunction::ToString() const
{
    return "(exp " + ArgString() + ")";
}

pp::Arity ExpFunctionGenerator::GetArity() const
{
    return Arity::Unary;
}

pp::IFunctionPtr ExpFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<ExpFunction>(std::move(arg));
}

// --------------------------------------------------------------------

LogFunction::LogFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float LogFunction::Eval(float x, float y) const
{
    // TODO-jrk: deal with negative args
    return std::log(EvalArg(x, y));
}

std::string LogFunction::ToString() const
{
    return "(ln " + ArgString() + ")";
}

pp::Arity LogFunctionGenerator::GetArity() const
{
    return Arity::Unary;
}

pp::IFunctionPtr LogFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<LogFunction>(std::move(arg));
}
