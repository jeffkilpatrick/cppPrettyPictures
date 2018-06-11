#include "gtest/gtest.h"
#include "pp/Eval.h"
#include "pp/fun/CoordinateFunction.h"

TEST(EvalTest, Basics) {
    pp::Image img = pp::Eval(pp::XFunction{}, 2, 2);

    EXPECT_EQ(pp::Color{-1.f}, img(0, 0));
    EXPECT_EQ(pp::Color{ 0.f}, img(1, 0));
    EXPECT_EQ(pp::Color{-1.f}, img(0, 1));
    EXPECT_EQ(pp::Color{ 0.f}, img(1, 1));
}
