#include "gtest/gtest.h"
#include "pp/fun/CoordinateFunction.h"
#include "pp/fun/InnerProductFunction.h"

using pp::Color;
using pp::XFunctionGenerator;
using pp::YFunctionGenerator;

TEST(InnerProductFunctionTest, Basics) {
    auto f = pp::InnerProductFunctionGenerator{}
        .Make(XFunctionGenerator{}.Make(), YFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(Color{0.6f}, f->Eval(0.2f, 1.f));
    EXPECT_EQ(Color{1.2f}, f->Eval(0.4f, 1.f));
}
