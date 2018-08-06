#include "pp/Color.h"

#include <ostream>

using pp::Color;

bool pp::operator==(const Color& a, const Color& b)
{
    return a.C1 == b.C1
        && a.C2 == b.C2
        && a.C3 == b.C3;
}

std::ostream& pp::operator<<(std::ostream& s, const Color& c)
{
    s << "Color{" << c.C1 << ", " << c.C2 << ", " << c.C3 << "}";
    return s;
}