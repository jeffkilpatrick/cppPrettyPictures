#include "pp/serialize/Token.h"

#include <ostream>

using pp::Token;

/*static*/ const Token Token::End(TokenType::End, "<eof>");
/*static*/ Token Token::Whitespace(std::string&& val)
    { return Token(TokenType::Whitespace, std::move(val)); }
/*static*/ const Token Token::OpenParen(TokenType::OpenParen, "(");
/*static*/ const Token Token::CloseParen(TokenType::CloseParen, ")");
/*static*/ Token Token::Identifier(std::string&& val)
    { return Token(TokenType::Identifier, std::move(val)); }
/*static*/ Token Token::Real(float val) { return Token(TokenType::Real, val); }

Token::Token(TokenType type, std::string&& val)
    : m_type(type)
    , m_val(std::move(val))
{ }

Token::Token(TokenType type, float val)
    : m_type(type)
    , m_val(val)
{ }

bool Token::operator==(const Token& other) const
{
    return m_type == other.m_type && m_val == other.m_val;
}

pp::TokenType Token::GetType() const
{
    return m_type;
}

const std::string& Token::GetString() const
{
    return boost::get<std::string>(m_val);
}

float Token::GetReal() const
{
    return boost::get<float>(m_val);
}

std::ostream& pp::operator<<(std::ostream& s, const Token& t)
{
    s << "Token{type=" << static_cast<int>(t.m_type) << ", val='" << t.m_val << "'}";
    return s;
}
