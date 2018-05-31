#pragma once

#include "pp/utility/Exports.h"

#include <functional>
#include <random>
#include <vector>

namespace pp {
    using IFunctionGeneratorPtr = std::unique_ptr<class IFunctionGenerator>;

    class PP_EXPORT Registry
    {
    public:
        using GeneratorFactory = std::function<IFunctionGeneratorPtr()>;

        Registry();
        Registry& operator=(const Registry&) = delete;
        Registry& operator=(Registry&&) = delete;

        IFunctionGeneratorPtr GetRandom();

    private:
        std::mt19937 m_gen;
        std::vector<GeneratorFactory> m_registry;
    };
}
