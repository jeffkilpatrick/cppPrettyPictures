#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"
#include "pp/fun/RoundFunction.h"

namespace pp {

    class PP_EXPORT DissolveFunction final : public ITrinaryFunction {
    public:
        DissolveFunction(IFunctionPtr fun0, IFunctionPtr fun1, IFunctionPtr fun2);

        float EvalSingle(float x, float y, float a0, float a1, float a2) const override;
        const std::string& GetName() const override;

    private:
        WrapFunction m_truncate;
    };

    class PP_EXPORT DissolveFunctionGenerator final : public ITrinaryFunctionGenerator {
    public:
        IFunctionPtr Make(IFunctionPtr arg0, IFunctionPtr arg1, IFunctionPtr arg2) override;
    };
}