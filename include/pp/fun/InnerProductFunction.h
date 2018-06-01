#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"
#include "pp/utility/Exports.h"

namespace pp {

    class PP_EXPORT InnerProductFunction final : public IFunction {
    public:
        InnerProductFunction(IFunctionPtr fun0, IFunctionPtr fun1);

        Color Eval(float x, float y) const override;
        std::string ToString() const override;

    private:
        IFunctionPtr m_fun0;
        IFunctionPtr m_fun1;
    };

    class PP_EXPORT InnerProductFunctionGenerator final : public IBinaryFunctionGenerator {
    public:
        IFunctionPtr Make(IFunctionPtr arg0, IFunctionPtr arg1) override;
    };
}