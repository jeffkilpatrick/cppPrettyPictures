#include "pp/Generate.h"
#include "pp/Registry.h"
#include "pp/fun/Arity.h"
#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

using pp::Arity;

pp::IFunctionPtr pp::RandomExpression(Registry& r)
{
    auto fg = r.GetRandom();

    switch (fg->GetArity())
    {
        case Arity::Nonary:
            return dynamic_cast<INonaryFunctionGenerator&>(*fg).Make();

        case Arity::Unary:
            return dynamic_cast<IUnaryFunctionGenerator&>(*fg)
                .Make(RandomExpression(r));

        case Arity::Binary:
            return dynamic_cast<IBinaryFunctionGenerator&>(*fg)
                .Make(RandomExpression(r), RandomExpression(r));

        case Arity::Trinary:
            return dynamic_cast<ITrinaryFunctionGenerator&>(*fg)
                .Make(RandomExpression(r), RandomExpression(r), RandomExpression(r));
    }

    return nullptr;
}