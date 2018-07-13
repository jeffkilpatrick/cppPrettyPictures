#include "pp/expr/Generate.h"
#include "pp/fun/Arity.h"
#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"
#include "pp/fun/Registry.h"

using pp::Arity;

static pp::IFunctionPtr RandomExpressionImpl(pp::Registry& r, pp::Range depth, uint16_t currentDepth)
{
    using namespace pp;

    IFunctionGeneratorPtr fg;
    if (currentDepth >= depth.Max)
    {
        fg = r.GetRandomNonary();
    }
    else if (currentDepth + 1 < depth.Min)
    {
        fg = r.GetRandomNonNonary();
    }
    else
    {
        fg = r.GetRandom();
    }

    switch (fg->GetArity())
    {
        case Arity::Nonary:
            return dynamic_cast<INonaryFunctionGenerator&>(*fg).Make();

        case Arity::Unary:
            return dynamic_cast<IUnaryFunctionGenerator&>(*fg)
                .Make(
                    RandomExpressionImpl(r, depth, currentDepth + 1));

        case Arity::Binary:
            return dynamic_cast<IBinaryFunctionGenerator&>(*fg)
                .Make(
                    RandomExpressionImpl(r, depth, currentDepth + 1),
                    RandomExpressionImpl(r, depth, currentDepth + 1));

        case Arity::Trinary:
            return dynamic_cast<ITrinaryFunctionGenerator&>(*fg)
                .Make(
                    RandomExpressionImpl(r, depth, currentDepth + 1),
                    RandomExpressionImpl(r, depth, currentDepth + 1),
                    RandomExpressionImpl(r, depth, currentDepth + 1));
    }

    return nullptr;
}

pp::IFunctionPtr pp::RandomExpression(Registry& r, pp::Range depth)
{
    return RandomExpressionImpl(r, depth, /*currentDepth*/ 0);
}