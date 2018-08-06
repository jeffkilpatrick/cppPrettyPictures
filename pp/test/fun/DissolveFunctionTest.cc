#include "gtest/gtest.h"
#include "pp/fun/ConstantFunction.h"
#include "pp/fun/CoordinateFunction.h"
#include "pp/fun/DissolveFunction.h"

using pp::Color;
using pp::XFunctionGenerator;
using pp::YFunctionGenerator;

TEST(DissolveFunctionTest, Basics) {
    auto f = pp::DissolveFunctionGenerator{}
        .Make(
            XFunctionGenerator{}.Make(),
            YFunctionGenerator{}.Make(),
            std::make_unique<pp::ConstantFunction>(Color{0.2f}));
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(Color{1.8f}, f->Eval(1.f, 2.f));
}