#pragma once

#include "pp/Color.h"
#include "pp/utility/Exports.h"

#include <memory>
#include <string>
#include <vector>

namespace pp {

    using IFunctionPtr = std::shared_ptr<class IFunction>;
    using IFunctionPtrVec = std::vector<IFunctionPtr>;

    class PP_EXPORT IFunction
    {
    public:
        virtual ~IFunction();
        Color Eval(float x, float y) const;
        virtual void EvalRow(const std::vector<float>& xs, float y, Color* out) const = 0;
        virtual const std::string& GetName() const = 0;

        const IFunctionPtrVec& GetArgs() const;

        bool Equals(const IFunction& other) const;

    protected:
        IFunction();
        IFunction(IFunctionPtr arg0);
        IFunction(IFunctionPtr arg0, IFunctionPtr arg1);
        IFunction(IFunctionPtr arg0, IFunctionPtr arg1, IFunctionPtr arg2);

    private:
        IFunctionPtrVec m_args;
    };

    /** A function taking no arguments **/
    class PP_EXPORT INonaryFunction : public IFunction
    {
    public:
        INonaryFunction();

        /** Evaluate the function for a single color channel **/
        virtual float EvalSingle(float x, float y) const = 0;
    };

    /** A function taking one argument **/
    class PP_EXPORT IUnaryFunction : public IFunction
    {
    public:
        IUnaryFunction(IFunctionPtr arg);

        /** Evaluate the function for a single color channel **/
        virtual float EvalSingle(float x, float y, float a) const = 0;

        /** Evaluate the function for multiple xs on all color channels. **/
        void EvalRow(const std::vector<float>& xs, float y, Color* out) const override;
    };

    /** A function taking two arguments **/
    class PP_EXPORT IBinaryFunction : public IFunction
    {
    public:
        IBinaryFunction(IFunctionPtr arg0, IFunctionPtr arg1);

        /** Evaluate the function for a single color channel **/
        virtual float EvalSingle(float x, float y, float a0, float a1) const = 0;

        /** Evaluate the function for multiple xs on all color channels. **/
        void EvalRow(const std::vector<float>& xs, float y, Color* out) const override;
    };

    /** A function taking three arguments **/
    class PP_EXPORT ITrinaryFunction : public IFunction
    {
    public:
        ITrinaryFunction(IFunctionPtr arg0, IFunctionPtr arg1, IFunctionPtr arg2);

        /** Evaluate the function for a single color channel **/
        virtual float EvalSingle(float x, float y, float a0, float a1, float a2) const = 0;

        /** Evaluate the function for multiple xs on all color channels. **/
        void EvalRow(const std::vector<float>& xs, float y, Color* out) const override;
    };
}
