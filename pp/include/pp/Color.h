#pragma once

#include "pp/utility/Exports.h"

#include <ios>

namespace pp {

    struct PP_EXPORT Color {
        explicit Color(float c) : C1(c), C2(c), C3(c) { }
        Color(float c1, float c2, float c3) : C1(c1), C2(c2), C3(c3) { }

        float C1; // R or Y
        float C2; // G or Cb
        float C3; // B or Cr
    };

    PP_EXPORT bool operator==(const Color& a, const Color& b);
    PP_EXPORT std::ostream& operator<<(std::ostream& s, const Color& c);
}