#include "pp/fun/IFunction.h"

using pp::IFunction;
using pp::IUnaryFunction;
using pp::IBinaryFunction;
using pp::ITrinaryFunction;

IFunction::~IFunction() = default;

IUnaryFunction::IUnaryFunction(IFunctionPtr fun)
    : m_fun(std::move(fun))
{ }

float IUnaryFunction::EvalArg(float x, float y) const
{
    return m_fun->Eval(x, y);
}
