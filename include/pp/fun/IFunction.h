#pragma once

#include "pp/Color.h"
#include "pp/utility/Exports.h"
#include <ios>
#include <memory>
#include <string>

namespace pp {

    using IFunctionPtr = std::unique_ptr<class IFunction>;

    class PP_EXPORT IFunction
    {
    public:
        virtual ~IFunction();

        virtual Color Eval(float x, float y) const = 0;
        virtual std::string ToString() const = 0;
    };

    /** A function taking no arguments **/
    class PP_EXPORT INonaryFunction : public IFunction
    {
    public:
        /** Evaluate the function for a single color channel **/
        virtual float EvalSingle(float x, float y) const = 0;

        /** Evaluate the function for all color channels **/
        Color Eval(float x, float y) const final;
    };

    /** A function taking one argument **/
    class PP_EXPORT IUnaryFunction : public IFunction
    {
    public:
        IUnaryFunction(IFunctionPtr fun);

        /** Evaluate the function for a single color channel **/
        virtual float EvalSingle(float x, float y, float a) const = 0;

        /** Evaluate the function for all color channels **/
        Color Eval(float x, float y) const final;

    protected:
        std::string ArgString() const;

    private:
        IFunctionPtr m_fun;
    };

    /** A function taking two arguments **/
    class PP_EXPORT IBinaryFunction : public IFunction
    {
    public:
        IBinaryFunction(IFunctionPtr fun0, IFunctionPtr fun1);

        /** Evaluate the function for a single color channel **/
        virtual float EvalSingle(float x, float y, float a0, float a1) const = 0;

        /** Evaluate the function for all color channels **/
        Color Eval(float x, float y) const final;

    protected:
        std::string Arg0String() const;
        std::string Arg1String() const;

    private:
        IFunctionPtr m_fun0;
        IFunctionPtr m_fun1;
    };

    /** A function taking three arguments **/
    class PP_EXPORT ITrinaryFunction : public IFunction
    {
    public:
        ITrinaryFunction(IFunctionPtr fun0, IFunctionPtr fun1, IFunctionPtr fun2);

        /** Evaluate the function for a single color channel **/
        virtual float EvalSingle(float x, float y, float a0, float a1, float a2) const = 0;

        /** Evaluate the function for all color channels **/
        Color Eval(float x, float y) const final;

    private:
        IFunctionPtr m_fun0;
        IFunctionPtr m_fun1;
        IFunctionPtr m_fun2;
    };

    PP_EXPORT std::ostream& operator<<(std::ostream& s, const IFunction& fun);
}