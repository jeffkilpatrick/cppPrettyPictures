#include "pp/serialize/Scanner.h"

using pp::Scanner;
using pp::Token;

Scanner::Scanner(std::string&& str)
    : m_str(std::move(str))
    , m_cursor(m_str.c_str())
    , m_limit(m_str.c_str() + m_str.size())
    , m_marker(nullptr)
{ }

static Token LexWhitespace(const char* start, const char* end)
{
    return Token::Whitespace(std::string(start, end - start));
}

static Token LexIdentifier(const char* start, const char* end)
{
    return Token::Identifier(std::string(start, end - start));
}

static Token LexReal(const char* start, const char* end)
{
    // Stuff the value into a string to ensure it's null terminated
    std::string s(start, end - start);
    auto val = std::strtof(s.c_str(), nullptr);

    return Token::Real(val);
}

Token Scanner::Next()
{
    auto next = NextImpl();

    while (next.GetType() == TokenType::Whitespace)
    {
        next = NextImpl();
    }

    return next;
}

Token Scanner::Next(TokenType expected)
{
    auto next = Next();

    if (next.GetType() != expected)
    {
        throw std::range_error("Unexpected token");
    }

    return next;
}

Token Scanner::NextImpl()
{
    if (m_cursor == m_limit)
    {
        return Token::End;
    }

    const char* start = m_cursor;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:define:YYCURSOR = m_cursor;
        re2c:define:YYLIMIT = m_limit;
        re2c:define:YYMARKER = m_marker;
        re2c:yyfill:enable = 0;

        letter = [a-zA-Z];

        *                              { throw std::domain_error("Illegal token"); }
        [ \t\r\n]+                     { return LexWhitespace(start, m_cursor); }
        "("                            { return Token::OpenParen; }
        ")"                            { return Token::CloseParen; }
        "const"                        { return Token::Const; }
        "-"? [1-9][0-9]*               { return LexReal(start, m_cursor); }
        "-"? [0-9]+ "."                { return LexReal(start, m_cursor); }
        "-"? [0-9]? "." [0-9]+         { return LexReal(start, m_cursor); }
        letter ("-"|letter|[0-9])*     { return LexIdentifier(start, m_cursor); }
    */

    throw std::domain_error("Illegal token");
}