#include "gtest/gtest.h"
#include "pp/Color.h"
#include "pp/fun/CoordinateFunction.h"
#include "pp/fun/RoundFunction.h"

using pp::Color;
using pp::XFunctionGenerator;

TEST(RoundFunctionTest, Abs) {
    auto f = pp::AbsFunctionGenerator{}.Make(XFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);


    EXPECT_EQ(Color{0.1f}, f->Eval(0.1f, 0));
    EXPECT_EQ(Color{1.f}, f->Eval(1.f, 0));
    EXPECT_EQ(Color{0.1f}, f->Eval(-0.1f, 0));
    EXPECT_EQ(Color{0.f}, f->Eval(0.f, 0));
    EXPECT_EQ(Color{0.f}, f->Eval(-0.f, 0));
    EXPECT_EQ(Color{1.f}, f->Eval(-1.f, 0));
}

TEST(RoundFunctionTest, Clip) {
    auto f = pp::ClipFunctionGenerator{}.Make(XFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(Color{0.1f}, f->Eval(0.1f, 0));
    EXPECT_EQ(Color{1.0f}, f->Eval(1.5f, 0));
    EXPECT_EQ(Color{-1.0f}, f->Eval(-1.5f, 0));
}

TEST(RoundFunctionTest, Down) {
    auto f = pp::RoundDownFunctionGenerator{}.Make(XFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(Color{0.f}, f->Eval(0.1f, 0));
    EXPECT_EQ(Color{1.f}, f->Eval(1.f, 0));
    EXPECT_EQ(Color{-1.f}, f->Eval(-0.1f, 0));
    EXPECT_EQ(Color{0.f}, f->Eval(0.f, 0));
    EXPECT_EQ(Color{0.f}, f->Eval(-0.f, 0));
    EXPECT_EQ(Color{-1.f}, f->Eval(-1.f, 0));
}

TEST(RoundFunctionTest, Up) {
    auto f = pp::RoundUpFunctionGenerator{}.Make(XFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(Color{1.f}, f->Eval(0.1f, 0));
    EXPECT_EQ(Color{1.f}, f->Eval(1.f, 0));
    EXPECT_EQ(Color{0.f}, f->Eval(-0.1f, 0));
    EXPECT_EQ(Color{0.f}, f->Eval(0.f, 0));
    EXPECT_EQ(Color{0.f}, f->Eval(-0.f, 0));
    EXPECT_EQ(Color{-1.f}, f->Eval(-1.f, 0));
}

TEST(RoundFunctionTest, Wrap) {
    auto f = pp::WrapFunctionGenerator{}.Make(XFunctionGenerator{}.Make());
    ASSERT_NE(nullptr, f);

    EXPECT_EQ(Color{0.5f}, f->Eval(0.5f, 0));
    EXPECT_EQ(Color{-0.5f}, f->Eval(1.5f, 0));
    EXPECT_EQ(Color{0.5f}, f->Eval(-1.5f, 0));
    EXPECT_EQ(Color{0.f}, f->Eval(10.f, 0));
}
