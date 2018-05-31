#include "gtest/gtest.h"
#include "pp/fun/CoordinateFunction.h"

using pp::XFunction;
using pp::XFunctionGenerator;
using pp::YFunction;
using pp::YFunctionGenerator;

TEST(XFunctionTest, Basics) {
    XFunction f;
    EXPECT_EQ(0.1f, f.Eval(0.1f, 0));
    EXPECT_EQ(0.2f, f.Eval(0.2f, 0));
    EXPECT_EQ(0.3f, f.Eval(0.3f, 0));
}

TEST(XFunctionTest, Make) {
    XFunctionGenerator fg;
    auto f = fg.Make();
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(0.1f, f->Eval(0.1f, 0));
    EXPECT_EQ(0.2f, f->Eval(0.2f, 0));
    EXPECT_EQ(0.3f, f->Eval(0.3f, 0));
}

TEST(YFunctionTest, Basics) {
    YFunction f;
    EXPECT_EQ(0.1f, f.Eval(0, 0.1f));
    EXPECT_EQ(0.2f, f.Eval(0, 0.2f));
    EXPECT_EQ(0.3f, f.Eval(0, 0.3f));
}

TEST(YFunctionTest, Make) {
    YFunctionGenerator fg;
    auto f = fg.Make();
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(0.1f, f->Eval(0, 0.1f));
    EXPECT_EQ(0.2f, f->Eval(0, 0.2f));
    EXPECT_EQ(0.3f, f->Eval(0, 0.3f));
}
