#include "gtest/gtest.h"
#include "pp/fun/CoordinateFunction.h"
#include "pp/fun/ArithmeticFunction.h"

using pp::Color;
using pp::XFunctionGenerator;
using pp::YFunctionGenerator;

TEST(ArithmeticFunctionTest, Add) {
    auto f = pp::AddFunctionGenerator{}
        .Make(XFunctionGenerator{}.Make(), YFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(Color{0.11f}, f->Eval(0.1f, 0.01f));
    EXPECT_EQ(Color{0.22f}, f->Eval(0.2f, 0.02f));
    EXPECT_EQ(Color{0.33f}, f->Eval(0.3f, 0.03f));
}

TEST(ArithmeticFunctionTest, Divide) {
    auto f = pp::DivideFunctionGenerator{}
        .Make(XFunctionGenerator{}.Make(), YFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(Color{1.}, f->Eval(2.0f, 2.f));
    EXPECT_EQ(Color{2.}, f->Eval(6.0f, 3.f));
    EXPECT_EQ(Color{2.}, f->Eval(8.0f, 4.f));
}

TEST(ArithmeticFunctionTest, Multiply) {
    auto f = pp::MultiplyFunctionGenerator{}
        .Make(XFunctionGenerator{}.Make(), YFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(Color{0.2f}, f->Eval(0.1f, 2.f));
    EXPECT_EQ(Color{0.6f}, f->Eval(0.2f, 3.f));
    EXPECT_EQ(Color{1.2f}, f->Eval(0.3f, 4.f));
}

TEST(ArithmeticFunctionTest, Subtract) {
    auto f = pp::SubtractFunctionGenerator{}
        .Make(XFunctionGenerator{}.Make(), YFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(Color{0.09f}, f->Eval(0.1f, 0.01f));
    EXPECT_EQ(Color{0.18f}, f->Eval(0.2f, 0.02f));
    EXPECT_EQ(Color{0.27f}, f->Eval(0.3f, 0.03f));
}
