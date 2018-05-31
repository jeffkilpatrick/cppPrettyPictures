#include "gtest/gtest.h"
#include "pp/fun/CoordinateFunction.h"
#include "pp/fun/RoundFunction.h"

using pp::RoundDownFunction;
using pp::RoundDownFunctionGenerator;
using pp::RoundUpFunction;
using pp::RoundUpFunctionGenerator;
using pp::XFunction;
using pp::XFunctionGenerator;

TEST(RoundUpFunctionTest, Basics) {
    RoundUpFunction f(XFunctionGenerator{}.Make());
    EXPECT_EQ(1.f, f.Eval(0.1f, 0));
    EXPECT_EQ(1.f, f.Eval(1.f, 0));
    EXPECT_EQ(0.f, f.Eval(-0.1f, 0));
    EXPECT_EQ(0.f, f.Eval(0.f, 0));
    EXPECT_EQ(0.f, f.Eval(-0.f, 0));
    EXPECT_EQ(-1.f, f.Eval(-1.f, 0));
}

TEST(RoundUpFunctionTest, Make) {
    RoundUpFunctionGenerator fg;
    auto f = fg.Make(XFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(1.f, f->Eval(0.1f, 0));
}

TEST(RoundDownFunctionTest, Basics) {
    RoundDownFunction f(XFunctionGenerator{}.Make());
    EXPECT_EQ(0.f, f.Eval(0.1f, 0));
    EXPECT_EQ(1.f, f.Eval(1.f, 0));
    EXPECT_EQ(-1.f, f.Eval(-0.1f, 0));
    EXPECT_EQ(0.f, f.Eval(0.f, 0));
    EXPECT_EQ(0.f, f.Eval(-0.f, 0));
    EXPECT_EQ(-1.f, f.Eval(-1.f, 0));
}

TEST(RoundDownFunctionTest, Make) {
    RoundDownFunctionGenerator fg;
    auto f = fg.Make(XFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(0.f, f->Eval(0.1f, 0));
}
