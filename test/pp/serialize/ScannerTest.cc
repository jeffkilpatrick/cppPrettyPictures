#include "gtest/gtest.h"
#include "pp/serialize/Scanner.h"

using pp::Scanner;
using pp::Token;

static void TestSingle(const Token& expected, std::string&& input)
{
    Scanner s(std::move(input));
    EXPECT_EQ(expected, s.Next());
    EXPECT_EQ(Token::End, s.Next());
}

TEST(ScannerTest, SingleToken) {
    TestSingle(Token::OpenParen, "(");
    TestSingle(Token::CloseParen, ")");
    TestSingle(Token::Identifier("pants"), "pants");
    TestSingle(Token::Identifier("hyphen-ated"), "hyphen-ated");

    TestSingle(Token::Real(1.f), "1");
    TestSingle(Token::Real(-1.f), "-1");
    TestSingle(Token::Real(1.f), "1.");
    TestSingle(Token::Real(-1.f), "-1.");
    TestSingle(Token::Real(1.2f), "1.2");
    TestSingle(Token::Real(-1.2f), "-1.2");
    TestSingle(Token::Real(.2f), ".2");
    TestSingle(Token::Real(-.2f), "-.2");
}

TEST(ScannerTest, MultiToken) {
    Scanner s("(a-constant -.2)");

    EXPECT_EQ(Token::OpenParen, s.Next());
    EXPECT_EQ(Token::Identifier("a-constant"), s.Next());
    EXPECT_EQ(Token::Real(-.2f), s.Next());
    EXPECT_EQ(Token::CloseParen, s.Next());
    EXPECT_EQ(Token::End, s.Next());
}
