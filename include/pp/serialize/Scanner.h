#pragma once

#include "pp/serialize/Token.h"

namespace pp {

    class PP_EXPORT Scanner {
    public:
        Scanner(std::string&& str);

        Token Next();
        Token Next(TokenType expected);

    private:

        Token NextImpl();

        std::string m_str;
        const char* m_cursor;
        const char* m_limit;
        const char* m_marker;
    };
}