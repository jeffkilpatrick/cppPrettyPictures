#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

#include <random>

namespace pp {
    class ConstantFunction : public INonaryFunction {
    public:
        ConstantFunction(float constant);

        float Eval(float x, float y) const override;

    private:
        float m_constant;
    };

    class ConstantFunctionGenerator : public INonaryFunctionGenerator {
    public:
        ConstantFunctionGenerator();
        Arity GetArity() const override;
        IFunctionPtr Make() override;
 
    private:
        std::mt19937 m_gen;
    };
}
