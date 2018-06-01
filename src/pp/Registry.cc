#include "pp/Registry.h"

#include "pp/fun/ArithmeticFunction.h"
#include "pp/fun/ConstantFunction.h"
#include "pp/fun/CoordinateFunction.h"
#include "pp/fun/LogFunction.h"
#include "pp/fun/InnerProductFunction.h"
#include "pp/fun/NegateFunction.h"
#include "pp/fun/RoundFunction.h"
#include "pp/fun/TrigFunction.h"

using pp::Registry;

Registry::Registry()
    : m_gen{std::random_device{}()}
    , m_registry{{
        // Nonary
        [](){ return std::make_unique<ConstantFunctionGenerator>(); },
        [](){ return std::make_unique<XFunctionGenerator>(); },
        [](){ return std::make_unique<YFunctionGenerator>(); },

        // Unary
        [](){ return std::make_unique<NegateFunctionGenerator>(); },
        [](){ return std::make_unique<AbsFunctionGenerator>(); },
        [](){ return std::make_unique<ClipFunctionGenerator>(); },
        [](){ return std::make_unique<RoundDownFunctionGenerator>(); },
        [](){ return std::make_unique<RoundUpFunctionGenerator>(); },
        [](){ return std::make_unique<WrapFunctionGenerator>(); },

        [](){ return std::make_unique<AtanFunctionGenerator>(); },
        [](){ return std::make_unique<CosFunctionGenerator>(); },
        [](){ return std::make_unique<SinFunctionGenerator>(); },
        [](){ return std::make_unique<ExpFunctionGenerator>(); },
        [](){ return std::make_unique<LogFunctionGenerator>(); },

        // Binary
        [](){ return std::make_unique<AddFunctionGenerator>(); },
        [](){ return std::make_unique<SubtractFunctionGenerator>(); },
        [](){ return std::make_unique<MultiplyFunctionGenerator>(); },
        [](){ return std::make_unique<DivideFunctionGenerator>(); },

        // Other
        [](){ return std::make_unique<InnerProductFunctionGenerator>(); },

    }}
{ }

pp::IFunctionGeneratorPtr Registry::GetRandom()
{
    auto r = m_gen() % m_registry.size();
    return m_registry.at(r)();
}

pp::IFunctionGeneratorPtr Registry::GetRandomNonary()
{
    auto r = m_gen() % 3;
    return m_registry.at(r)();
}