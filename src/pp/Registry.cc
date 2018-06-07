#include "pp/Registry.h"

#include "pp/fun/ArithmeticFunction.h"
#include "pp/fun/ColorSpaceFunction.h"
#include "pp/fun/ConstantFunction.h"
#include "pp/fun/CoordinateFunction.h"
#include "pp/fun/DissolveFunction.h"
#include "pp/fun/LogFunction.h"
#include "pp/fun/InnerProductFunction.h"
#include "pp/fun/NegateFunction.h"
#include "pp/fun/NoiseFunction.h"
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

        [](){ return std::make_unique<ColorNoiseFunctionGenerator>(); },
        [](){ return std::make_unique<GrayscaleNoiseFunctionGenerator>(); },

        // Trinary
        [](){ return std::make_unique<DissolveFunctionGenerator>(); },

        // Other
        [](){ return std::make_unique<InnerProductFunctionGenerator>(); },
        [](){ return std::make_unique<RgbToYCbCrFunctionGenerator>(); },
        [](){ return std::make_unique<YCbCrToRgbFunctionGenerator>(); },

    }}
{
    for (size_t i = 0; i < m_registry.size(); ++i)
    {
        const auto& name = m_registry[i]()->GetName();
        m_index[name] = i;
    }
}

pp::IFunctionGeneratorPtr Registry::Get(const std::string& name) const
{
    auto index = m_index.at(name);
    return m_registry.at(index)();
}

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