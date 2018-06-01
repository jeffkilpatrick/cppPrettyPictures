#include "pp/fun/LogFunction.h"

using pp::ExpFunction;
using pp::ExpFunctionGenerator;
using pp::LogFunction;
using pp::LogFunctionGenerator;

ExpFunction::ExpFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float ExpFunction::EvalSingle(float x, float y, float a) const
{
    return std::exp(a);
}

std::string ExpFunction::ToString() const
{
    return "(exp " + ArgString() + ")";
}

pp::IFunctionPtr ExpFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<ExpFunction>(std::move(arg));
}

// --------------------------------------------------------------------

LogFunction::LogFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float LogFunction::EvalSingle(float x, float y, float a) const
{
    // TODO-jrk: deal with negative args
    return std::log(a);
}

std::string LogFunction::ToString() const
{
    return "(ln " + ArgString() + ")";
}

pp::IFunctionPtr LogFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<LogFunction>(std::move(arg));
}
