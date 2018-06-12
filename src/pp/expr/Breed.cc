#include "pp/expr/Breed.h"
#include "pp/fun/Arity.h"
#include "pp/fun/IFunctionGenerator.h"
#include "pp/fun/Registry.h"

#include <random>

pp::IFunctionPtr pp::Breed(const IFunctionPtr& parent1, const IFunctionPtr& parent2, const Registry& registry)
{
    std::random_device r;

    if (typeid(parent1) != typeid(parent2))
    {
        // Non-compatible functions: pick one at random
        return (r() % 2) ? parent1 : parent2;
    }

    // Compatible functions: randomly pick arguments
    auto args = parent1->GetArgs();
    for (size_t i = 0; i < args.size(); ++i)
    {
        if (r() % 2)
        {
            args[i] = parent2->GetArgs().at(i);
        }
    }

    auto factory = registry.Get(parent1->GetName());

    switch (factory->GetArity())
    {
    case Arity::Nonary:
        return parent1;

    case Arity::Unary:
        return dynamic_cast<IUnaryFunctionGenerator&>(*factory).Make(args.at(0));

    case Arity::Binary:
        return dynamic_cast<IBinaryFunctionGenerator&>(*factory).Make(args.at(0), args.at(1));

    case Arity::Trinary:
        return dynamic_cast<ITrinaryFunctionGenerator&>(*factory).Make(args.at(0), args.at(1), args.at(2));
    }

    return nullptr;
}
