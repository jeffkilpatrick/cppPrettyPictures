#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

namespace pp {

    class PP_EXPORT AddFunction final : public IBinaryFunction {
    public:
        AddFunction(IFunctionPtr arg0, IFunctionPtr arg1);

        float EvalSingle(float x, float y, float a0, float a1) const override;
        const std::string& GetName() const override;
    };

    class PP_EXPORT AddFunctionGenerator final : public IBinaryFunctionGenerator {
    public:
        IFunctionPtr Make(IFunctionPtr arg0, IFunctionPtr arg1) override;
        const std::string& GetName() const override;
    };

    // ---------------------------------------------------------------------------

    class PP_EXPORT SubtractFunction final : public IBinaryFunction {
    public:
        SubtractFunction(IFunctionPtr arg0, IFunctionPtr arg1);

        float EvalSingle(float x, float y, float a0, float a1) const override;
        const std::string& GetName() const override;
    };

    class PP_EXPORT SubtractFunctionGenerator final : public IBinaryFunctionGenerator {
    public:
        IFunctionPtr Make(IFunctionPtr arg0, IFunctionPtr arg1) override;
        const std::string& GetName() const override;
    };

    // ---------------------------------------------------------------------------

    class PP_EXPORT MultiplyFunction final : public IBinaryFunction {
    public:
        MultiplyFunction(IFunctionPtr arg0, IFunctionPtr arg1);

        float EvalSingle(float x, float y, float a0, float a1) const override;
        const std::string& GetName() const override;
    };

    class PP_EXPORT MultiplyFunctionGenerator final : public IBinaryFunctionGenerator {
    public:
        IFunctionPtr Make(IFunctionPtr arg0, IFunctionPtr arg1) override;
        const std::string& GetName() const override;
    };

    // ---------------------------------------------------------------------------

    class PP_EXPORT DivideFunction final : public IBinaryFunction {
    public:
        DivideFunction(IFunctionPtr arg0, IFunctionPtr arg1);

        float EvalSingle(float x, float y, float a0, float a1) const override;
        const std::string& GetName() const override;
    };

    class PP_EXPORT DivideFunctionGenerator final : public IBinaryFunctionGenerator {
    public:
        IFunctionPtr Make(IFunctionPtr arg0, IFunctionPtr arg1) override;
        const std::string& GetName() const override;
    };
}
