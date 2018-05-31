#pragma once

#include <memory>

namespace pp {

    enum class Arity;
    class IFunction;

    class IFunctionGenerator
    {
    public:
        using IFunctionPtr = std::unique_ptr<IFunction>;

        virtual ~IFunctionGenerator();

        virtual Arity GetArity() const = 0;
    };

    /** A generator of functions taking no arguments.  **/
    class INonaryFunctionGenerator : public IFunctionGenerator
    {
    public:
        virtual IFunctionPtr Make() = 0;
    };

    /** A generator of functions taking one argument. **/
    class IUnaryFunctionGenerator : public IFunctionGenerator
    {
    public:
        virtual IFunctionPtr Make(IFunctionPtr arg) = 0;
    };

    /** A generator of functions taking two arguments. **/
    class IBinaryFunctionGenerator : public IFunctionGenerator
    {
    public:
        virtual IFunctionPtr Make(IFunctionPtr arg0, IFunctionPtr arg1) = 0;
    };

    /** A generator of functions taking three arguments. **/
    class ITrinaryFunctionGenerator : public IFunctionGenerator
    {
    public:
        virtual IFunctionPtr Make(IFunctionPtr arg0, IFunctionPtr arg1, IFunctionPtr arg2) = 0;
    };
}
