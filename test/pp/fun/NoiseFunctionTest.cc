#include "gtest/gtest.h"
#include "pp/fun/ConstantFunction.h"
#include "pp/fun/NoiseFunction.h"

using pp::Color;
using pp::ColorNoiseFunctionGenerator;
using pp::GrayscaleNoiseFunctionGenerator;
using pp::ConstantFunctionGenerator;

TEST(NoiseFunctionTest, Color) {
    auto f = ColorNoiseFunctionGenerator{}
        .Make(std::make_unique<pp::ConstantFunction>(Color{0.1f, 0.2f, 0.3f}));
    ASSERT_NE(nullptr, f);
    EXPECT_EQ("color-noise", f->GetName());

    auto c = f->Eval(0.f, 0.f);
    EXPECT_NE(c.C1, c.C2);
    EXPECT_NE(c.C1, c.C3);
    EXPECT_NE(c.C2, c.C3);
}

TEST(NoiseFunctionTest, Grayscale) {
    auto f = GrayscaleNoiseFunctionGenerator{}
        .Make(std::make_unique<pp::ConstantFunction>(Color{0.1f, 0.2f, 0.3f}));
    ASSERT_NE(nullptr, f);
    EXPECT_EQ("grayscale-noise", f->GetName());

    auto c = f->Eval(0.f, 0.f);
    EXPECT_EQ(c.C1, c.C2);
    EXPECT_EQ(c.C1, c.C3);
    EXPECT_EQ(c.C2, c.C3);
}
