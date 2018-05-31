#include "gtest/gtest.h"
#include "pp/fun/ConstantFunction.h"

using pp::ConstantFunction;
using pp::ConstantFunctionGenerator;

TEST(ConstantFunctionTest, Basics) {
    ConstantFunction cf(0.1f);
    EXPECT_EQ(0.1f, cf.Eval(0, 0));
}

TEST(ConstantFunctionTest, Make) {
    ConstantFunctionGenerator cfg;
    auto cf = cfg.Make();
    ASSERT_NE(nullptr, cf);

    auto x = cf->Eval(0, 0);
    EXPECT_LE(-1, x);
    EXPECT_GE(1, x);
    EXPECT_EQ(x, cf->Eval(0.5, 0.5));
}
