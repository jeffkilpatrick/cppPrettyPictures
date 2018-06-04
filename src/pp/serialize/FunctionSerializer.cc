#include "pp/serialize/FunctionSerializer.h"

#include <sstream>

std::string pp::Serialize(const IFunction& fun)
{
    std::ostringstream str;
    str << fun;
    return str.str();
}

std::ostream& pp::operator<<(std::ostream& s, const IFunction& fun)
{
    s << '(' << fun.GetName();

    for (const auto& arg : fun.GetArgs())
    {
        s << ' ' << *arg;
    }

    s << ')';

    return s;
}
