#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

#include <random>

namespace pp {

    class PP_EXPORT AbsFunction final : public IUnaryFunction {
    public:
        AbsFunction(IFunctionPtr arg);

        float EvalSingle(float x, float y, float a) const override;
        std::string ToString() const override;
    };

    class PP_EXPORT AbsFunctionGenerator final : public IUnaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make(IFunctionPtr arg) override;
    };

    // ---------------------------------------------------------------------

    class PP_EXPORT ClipFunction final : public IUnaryFunction {
    public:
        ClipFunction(IFunctionPtr arg);

        float EvalSingle(float x, float y, float a) const override;
        std::string ToString() const override;
    };

    class PP_EXPORT ClipFunctionGenerator final : public IUnaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make(IFunctionPtr arg) override;
    };

    // ---------------------------------------------------------------------

    class PP_EXPORT RoundDownFunction final : public IUnaryFunction {
    public:
        RoundDownFunction(IFunctionPtr arg);

        float EvalSingle(float x, float y, float a) const override;
        std::string ToString() const override;
    };

    class PP_EXPORT RoundDownFunctionGenerator final : public IUnaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make(IFunctionPtr arg) override;
    };

    // ---------------------------------------------------------------------

    class PP_EXPORT RoundUpFunction final : public IUnaryFunction {
    public:
        RoundUpFunction(IFunctionPtr arg);

        float EvalSingle(float x, float y, float a) const override;
        std::string ToString() const override;
    };

    class PP_EXPORT RoundUpFunctionGenerator final : public IUnaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make(IFunctionPtr arg) override;
    };

    // ---------------------------------------------------------------------

    class PP_EXPORT WrapFunction final : public IUnaryFunction {
    public:
        WrapFunction(IFunctionPtr arg);

        float EvalSingle(float x, float y, float a) const override;
        std::string ToString() const override;
    };

    class PP_EXPORT WrapFunctionGenerator final : public IUnaryFunctionGenerator {
    public:
        Arity GetArity() const override;
        IFunctionPtr Make(IFunctionPtr arg) override;
    };}
