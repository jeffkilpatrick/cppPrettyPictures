#include "gtest/gtest.h"
#include "pp/fun/CoordinateFunction.h"

using pp::Color;
using pp::XFunction;
using pp::XFunctionGenerator;
using pp::YFunction;
using pp::YFunctionGenerator;

TEST(CoordinateFunctionTest, X) {
    auto f = XFunctionGenerator{}.Make();
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(Color{0.1f}, f->Eval(0.1f, 0));
    EXPECT_EQ(Color{0.2f}, f->Eval(0.2f, 0));
    EXPECT_EQ(Color{0.3f}, f->Eval(0.3f, 0));
}

TEST(CoordinateFunctionTest, Y) {
    auto f = YFunctionGenerator{}.Make();
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(Color{0.1f}, f->Eval(0, 0.1f));
    EXPECT_EQ(Color{0.2f}, f->Eval(0, 0.2f));
    EXPECT_EQ(Color{0.3f}, f->Eval(0, 0.3f));
}
