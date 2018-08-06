#include "gtest/gtest.h"
#include "pp/fun/CoordinateFunction.h"
#include "pp/fun/LogFunction.h"

using pp::Color;
using pp::ExpFunction;
using pp::ExpFunctionGenerator;
using pp::LogFunction;
using pp::LogFunctionGenerator;
using pp::XFunctionGenerator;

TEST(LogFunctionTest, Exp) {
    auto f = ExpFunctionGenerator{}.Make(XFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(Color{1.f}, f->Eval(0.0f, 0));
}

TEST(LogFunctionTest, Log) {
    auto f = LogFunctionGenerator{}.Make(XFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(Color{0.f}, f->Eval(1.0f, 0));
}
