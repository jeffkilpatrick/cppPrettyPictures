#include "gtest/gtest.h"
#include "pp/fun/CoordinateFunction.h"
#include "pp/fun/TrigFunction.h"

using pp::AtanFunction;
using pp::AtanFunctionGenerator;
using pp::CosFunction;
using pp::CosFunctionGenerator;
using pp::SinFunction;
using pp::SinFunctionGenerator;
using pp::XFunction;
using pp::XFunctionGenerator;

TEST(TrigFunctionTest, Atan) {
    auto f = AtanFunctionGenerator{}.Make(XFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);
    EXPECT_EQ(0.0f, f->Eval(0.0f, 0));
}

TEST(TrigFunctionTest, Cos) {
    auto f = CosFunctionGenerator{}.Make(XFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);
    EXPECT_EQ(1.0f, f->Eval(0.0f, 0));
}

TEST(TrigFunctionTest, Sin) {
    auto f = SinFunctionGenerator{}.Make(XFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);
    EXPECT_EQ(0.0f, f->Eval(0.0f, 0));
}
