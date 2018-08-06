#include "gtest/gtest.h"
#include "pp/fun/CoordinateFunction.h"
#include "pp/fun/NegateFunction.h"

using pp::Color;
using pp::NegateFunction;
using pp::NegateFunctionGenerator;
using pp::XFunction;
using pp::XFunctionGenerator;

TEST(NegateFunctionTest, Basics) {
    auto f = NegateFunctionGenerator{}.Make(XFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(Color{-0.1f}, f->Eval(0.1f, 0));
    EXPECT_EQ(Color{-0.2f}, f->Eval(0.2f, 0));
    EXPECT_EQ(Color{-0.3f}, f->Eval(0.3f, 0));
}
