#include "pp/Color.h"

using pp::Color;

PP_EXPORT bool pp::operator==(const Color& a, const Color& b)
{
    return a.C1 == b.C1
        && a.C2 == b.C2
        && a.C3 == b.C3;
}