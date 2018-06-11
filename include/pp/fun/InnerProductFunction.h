#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"
#include "pp/utility/Exports.h"

namespace pp {

    class PP_EXPORT InnerProductFunction final : public IFunction {
    public:
        InnerProductFunction(IFunctionPtr arg0, IFunctionPtr arg1);

        Color Eval(float x, float y) const override;
        void EvalRow(const std::vector<float>& xs, float y, Color* out) const override;
        const std::string& GetName() const override;
    };

    class PP_EXPORT InnerProductFunctionGenerator final : public IBinaryFunctionGenerator {
    public:
        IFunctionPtr Make(IFunctionPtr arg0, IFunctionPtr arg1) override;
        const std::string& GetName() const override;
    };
}