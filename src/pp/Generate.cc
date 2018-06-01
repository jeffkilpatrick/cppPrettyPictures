#include "pp/Generate.h"
#include "pp/Registry.h"
#include "pp/fun/Arity.h"
#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

using pp::Arity;

static pp::IFunctionPtr RandomExpressionImpl(pp::Registry& r, size_t maxDepth, size_t currentDepth)
{
    using namespace pp;

    auto fg = currentDepth >= maxDepth ? r.GetRandomNonary() : r.GetRandom();

    switch (fg->GetArity())
    {
        case Arity::Nonary:
            return dynamic_cast<INonaryFunctionGenerator&>(*fg).Make();

        case Arity::Unary:
            return dynamic_cast<IUnaryFunctionGenerator&>(*fg)
                .Make(
                    RandomExpressionImpl(r, maxDepth, currentDepth + 1));

        case Arity::Binary:
            return dynamic_cast<IBinaryFunctionGenerator&>(*fg)
                .Make(
                    RandomExpressionImpl(r, maxDepth, currentDepth + 1),
                    RandomExpressionImpl(r, maxDepth, currentDepth + 1));

        case Arity::Trinary:
            return dynamic_cast<ITrinaryFunctionGenerator&>(*fg)
                .Make(
                    RandomExpressionImpl(r, maxDepth, currentDepth + 1),
                    RandomExpressionImpl(r, maxDepth, currentDepth + 1),
                    RandomExpressionImpl(r, maxDepth, currentDepth + 1));
    }

    return nullptr;
}

pp::IFunctionPtr pp::RandomExpression(Registry& r, size_t maxDepth)
{
    return RandomExpressionImpl(r, maxDepth, /*maxDepth*/ 0);
}