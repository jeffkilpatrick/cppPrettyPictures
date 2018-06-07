#pragma once

#include "pp/utility/Exports.h"
#include <memory>

namespace pp {

    enum class Arity;
    class IFunction;

    class PP_EXPORT IFunctionGenerator
    {
    public:
        using IFunctionPtr = std::unique_ptr<IFunction>;

        virtual ~IFunctionGenerator();
        virtual const std::string& GetName() const = 0;

        virtual Arity GetArity() const = 0;
    };

    /** A generator of functions taking no arguments.  **/
    class PP_EXPORT INonaryFunctionGenerator : public IFunctionGenerator
    {
    public:
        virtual IFunctionPtr Make() = 0;
        Arity GetArity() const final;
    };

    /** A generator of functions taking one argument. **/
    class PP_EXPORT IUnaryFunctionGenerator : public IFunctionGenerator
    {
    public:
        virtual IFunctionPtr Make(IFunctionPtr arg) = 0;
        Arity GetArity() const final;
    };

    /** A generator of functions taking two arguments. **/
    class PP_EXPORT IBinaryFunctionGenerator : public IFunctionGenerator
    {
    public:
        virtual IFunctionPtr Make(IFunctionPtr arg0, IFunctionPtr arg1) = 0;
        Arity GetArity() const final;
    };

    /** A generator of functions taking three arguments. **/
    class PP_EXPORT ITrinaryFunctionGenerator : public IFunctionGenerator
    {
    public:
        virtual IFunctionPtr Make(IFunctionPtr arg0, IFunctionPtr arg1, IFunctionPtr arg2) = 0;
        Arity GetArity() const final;
    };
}
