#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

#include <random>

namespace pp {
    class PP_EXPORT ConstantFunction final : public INonaryFunction {
    public:
        ConstantFunction(float constant);

        float EvalSingle(float x, float y) const override;
        std::string ToString() const override;

    private:
        float m_constant;
    };

    class PP_EXPORT ConstantFunctionGenerator final : public INonaryFunctionGenerator {
    public:
        ConstantFunctionGenerator();
        Arity GetArity() const override;
        IFunctionPtr Make() override;
 
    private:
        std::mt19937 m_gen;
    };
}
