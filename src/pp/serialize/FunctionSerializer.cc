#include "pp/fun/ConstantFunction.h"
#include "pp/serialize/FunctionSerializer.h"

#include <sstream>

std::string pp::Serialize(const IFunction& fun)
{
    std::ostringstream str;
    str << fun;
    return str.str();
}

static void SerializeFunction(std::ostream& s, const pp::IFunction& fun)
{
    s << fun.GetName();

    for (const auto& arg : fun.GetArgs())
    {
        s << ' ' << *arg;
    }
}

static void SerializeConstant(std::ostream& s, const pp::ConstantFunction& fun)
{
    auto c = fun.Eval(0.f, 0.f);

    s << "const " << c.C1 << ' ' << c.C2 << ' ' << c.C3;
}

std::ostream& pp::operator<<(std::ostream& s, const IFunction& fun)
{
    s << '(';
 
    auto constFun = dynamic_cast<const pp::ConstantFunction*>(&fun);
    if (constFun)
    {
        SerializeConstant(s, *constFun);
    }
    else
    {
        SerializeFunction(s, fun);
    }

    s << ')';

    return s;
}
