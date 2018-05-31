#include "gtest/gtest.h"
#include "pp/fun/CoordinateFunction.h"
#include "pp/fun/RoundFunction.h"

using pp::RoundDownFunction;
using pp::RoundDownFunctionGenerator;
using pp::RoundUpFunction;
using pp::RoundUpFunctionGenerator;
using pp::XFunction;
using pp::XFunctionGenerator;

TEST(RoundFunctionTest, Up) {
    auto f = RoundUpFunctionGenerator{}.Make(XFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(1.f, f->Eval(0.1f, 0));
    EXPECT_EQ(1.f, f->Eval(1.f, 0));
    EXPECT_EQ(0.f, f->Eval(-0.1f, 0));
    EXPECT_EQ(0.f, f->Eval(0.f, 0));
    EXPECT_EQ(0.f, f->Eval(-0.f, 0));
    EXPECT_EQ(-1.f, f->Eval(-1.f, 0));
}

TEST(RoundFunctionTest, Down) {
    auto f = RoundDownFunctionGenerator{}.Make(XFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(0.f, f->Eval(0.1f, 0));
    EXPECT_EQ(1.f, f->Eval(1.f, 0));
    EXPECT_EQ(-1.f, f->Eval(-0.1f, 0));
    EXPECT_EQ(0.f, f->Eval(0.f, 0));
    EXPECT_EQ(0.f, f->Eval(-0.f, 0));
    EXPECT_EQ(-1.f, f->Eval(-1.f, 0));
}
