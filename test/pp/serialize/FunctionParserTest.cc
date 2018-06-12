#include "gtest/gtest.h"
#include "pp/fun/Registry.h"
#include "pp/serialize/FunctionParser.h"
#include "pp/serialize/FunctionSerializer.h"

using pp::Parse;

TEST(FunctionParserTest, Constant) {
    std::string expr("(const 0.1 0.2 0.3)");
    pp::Registry registry;

    auto x = Parse(std::string(expr), registry);
    ASSERT_NE(nullptr, x);
    EXPECT_EQ(expr, Serialize(*x));
}

TEST(FunctionParserTest, Nonary) {
    std::string expr("(x)");
    pp::Registry registry;

    auto x = Parse(std::string(expr), registry);
    ASSERT_NE(nullptr, x);
    EXPECT_EQ(expr, Serialize(*x));
}

TEST(FunctionParserTest, Unary) {
    std::string expr("(sin (x))");
    pp::Registry registry;

    auto x = Parse(std::string(expr), registry);
    ASSERT_NE(nullptr, x);
    EXPECT_EQ(expr, Serialize(*x));
}

TEST(FunctionParserTest, Binary) {
    std::string expr("(add (x) (y))");
    pp::Registry registry;

    auto x = Parse(std::string(expr), registry);
    ASSERT_NE(nullptr, x);
    EXPECT_EQ(expr, Serialize(*x));
}

TEST(FunctionParserTest, Trinary) {
    std::string expr("(dissolve (x) (y) (const 0.2 0.4 0.8))");
    pp::Registry registry;

    auto x = Parse(std::string(expr), registry);
    ASSERT_NE(nullptr, x);
    EXPECT_EQ(expr, Serialize(*x));
}
