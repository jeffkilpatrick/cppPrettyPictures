#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

#include <random>

namespace pp {
    class PP_EXPORT ConstantFunction final : public IFunction {
    public:
        ConstantFunction(Color constant);

        void EvalRow(const std::vector<float>& xs, float y, Color* out) const override;

        const std::string& GetName() const override;
        const Color& GetConstant() const;

    private:
        Color m_constant;
        std::string m_constantStr;
    };

    class PP_EXPORT ConstantFunctionGenerator final : public INonaryFunctionGenerator {
    public:
        ConstantFunctionGenerator();
        IFunctionPtr Make() override;
        const std::string& GetName() const override;

    private:
        std::mt19937 m_gen;
    };
}
