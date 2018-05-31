#pragma once

#include <ios>
#include <memory>
#include <string>

namespace pp {

    using IFunctionPtr = std::unique_ptr<class IFunction>;

    class IFunction
    {
    public:
        virtual ~IFunction();

        virtual float Eval(float x, float y) const = 0;
        virtual std::string ToString() const = 0;
    };

    /** A function taking no arguments **/
    class INonaryFunction : public IFunction
    { };

    /** A function taking one argument **/
    class IUnaryFunction : public IFunction
    {
    public:
        IUnaryFunction(IFunctionPtr fun);

    protected:
        float EvalArg(float x, float y) const;
        std::string ArgString() const;

    private:
        IFunctionPtr m_fun;
    };

    /** A function taking two arguments **/
    class IBinaryFunction : public IFunction
    {
    public:
        IBinaryFunction(IFunctionPtr fun0, IFunctionPtr fun1);

    protected:
        float EvalArg0(float x, float y) const;
        float EvalArg1(float x, float y) const;

    private:
        IFunctionPtr m_fun0;
        IFunctionPtr m_fun1;
    };

    /** A function taking three arguments **/
    class ITrinaryFunction : public IFunction
    {
    public:
        ITrinaryFunction(IFunctionPtr fun0, IFunctionPtr fun1, IFunctionPtr fun2);

    protected:
        float EvalArg0(float x, float y) const;
        float EvalArg1(float x, float y) const;
        float EvalArg2(float x, float y) const;

    private:
        IFunctionPtr m_fun0;
        IFunctionPtr m_fun1;
        IFunctionPtr m_fun2;
    };

    std::ostream& operator<<(std::ostream& s, const IFunction& fun);
}