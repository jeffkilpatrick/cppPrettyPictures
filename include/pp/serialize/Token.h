#pragma once

#include "pp/serialize/TokenType.h"
#include "pp/utility/Exports.h"

#include <boost/variant.hpp>
#include <ios>

namespace pp {
    class PP_EXPORT Token
    {
    public:
        static const Token End;
        static Token Whitespace(std::string&& val);
        static const Token OpenParen;
        static const Token CloseParen;
        static Token Identifier(std::string&& val);
        static Token Real(float val);

        bool operator==(const Token& other) const;

        TokenType GetType() const;

        float GetReal() const;
        const std::string& GetString() const;

    private:
        Token(TokenType type, std::string&& val);
        Token(TokenType type, float val);

        TokenType m_type;
        boost::variant<std::string, float> m_val;

        friend std::ostream& operator<<(std::ostream& s, const Token& t);
    };
}