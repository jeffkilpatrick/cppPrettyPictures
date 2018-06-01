#include "pp/fun/Arity.h"
#include "pp/fun/IFunctionGenerator.h"

using pp::Arity;

pp::IFunctionGenerator::~IFunctionGenerator() = default;

Arity pp::INonaryFunctionGenerator::GetArity() const
{
    return Arity::Nonary;
}

Arity pp::IUnaryFunctionGenerator::GetArity() const
{
    return Arity::Unary;
}

Arity pp::IBinaryFunctionGenerator::GetArity() const
{
    return Arity::Binary;
}

Arity pp::ITrinaryFunctionGenerator::GetArity() const
{
    return Arity::Trinary;
}
