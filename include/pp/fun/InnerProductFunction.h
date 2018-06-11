#pragma once

#include "pp/fun/DefaultFunction.h"
#include "pp/utility/Exports.h"

namespace pp {

    class PP_EXPORT InnerProductFunction final : public IFunction {
    public:
        struct Traits {
            static const char* GetName() { return "inner-product"; }
        };

        InnerProductFunction(IFunctionPtr arg0, IFunctionPtr arg1);

        void EvalRow(const std::vector<float>& xs, float y, Color* out) const override;
        const std::string& GetName() const override;
    };

    using InnerProductFunctionGenerator = DefaultBinaryFunctionGenerator<InnerProductFunction>;
}