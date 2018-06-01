#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

#include <random>

namespace pp {
    class PP_EXPORT ConstantFunction final : public IFunction {
    public:
        ConstantFunction(Color constant);

        Color Eval(float x, float y) const override;

        std::string ToString() const override;

    private:
        Color m_constant;
    };

    class PP_EXPORT ConstantFunctionGenerator final : public INonaryFunctionGenerator {
    public:
        ConstantFunctionGenerator();
        IFunctionPtr Make() override;
 
    private:
        std::mt19937 m_gen;
    };
}
