#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

#include <cmath>

namespace pp {

    template<typename TraitsT>
    class PP_EXPORT ArithmeticFunction : public IBinaryFunction {
    public:
        using Traits = TraitsT;
        ArithmeticFunction(IFunctionPtr arg0, IFunctionPtr arg1);
        float EvalSingle(float x, float y, float a0, float a1) const final;
        void EvalRow(const std::vector<float>& xs, float y, Color* out) const final;
        const std::string& GetName() const override;
    };

    template<typename GeneratedT>
    class PP_EXPORT ArithmeticFunctionGenerator : public IBinaryFunctionGenerator {
    public:
        const std::string& GetName() const override;
        IFunctionPtr Make(IFunctionPtr arg0, IFunctionPtr arg1) override;
    };

    // ---------------------------------------------------------------------------

    struct AddTraits {
        static float Eval(float a0, float a1) { return a0 + a1; }
        static const char* GetName() { return "add"; }
    };

    using AddFunction = ArithmeticFunction<AddTraits>;
    using AddFunctionGenerator = ArithmeticFunctionGenerator<AddFunction>;

    // ---------------------------------------------------------------------------

    struct SubtractTraits {
        static float Eval(float a0, float a1) { return a0 - a1; }
        static const char* GetName() { return "sub"; }
    };

    using SubtractFunction = ArithmeticFunction<SubtractTraits>;
    using SubtractFunctionGenerator = ArithmeticFunctionGenerator<SubtractFunction>;

    // ---------------------------------------------------------------------------

    struct MultiplyTraits {
        static float Eval(float a0, float a1) { return a0 * a1; }
        static const char* GetName() { return "mul"; }
    };

    using MultiplyFunction = ArithmeticFunction<MultiplyTraits>;
    using MultiplyFunctionGenerator = ArithmeticFunctionGenerator<MultiplyFunction>;

    // ---------------------------------------------------------------------------

    struct DivideTraits {
        static float Eval(float a0, float a1)
        {
            if (std::abs(a1) < 1e-3f)
            {
                a1 = std::copysign(1e-3f, a1);
            }

            return a0 / a1;
        }
        static const char* GetName() { return "div"; }
    };

    using DivideFunction = ArithmeticFunction<DivideTraits>;
    using DivideFunctionGenerator = ArithmeticFunctionGenerator<DivideFunction>;
}
