#include "gtest/gtest.h"
#include "pp/fun/ConstantFunction.h"
#include "pp/fun/CoordinateFunction.h"
#include "pp/fun/DissolveFunction.h"
#include "pp/fun/InnerProductFunction.h"
#include "pp/fun/NoiseFunction.h"
#include "pp/serialize/FunctionSerializer.h"

using pp::Serialize;

TEST(FunctionSerializerTest, Basics) {
    EXPECT_EQ("(x)", Serialize(pp::XFunction{}));
    EXPECT_EQ("(const 0.1 0.2 0.3)", Serialize(pp::ConstantFunction{pp::Color{0.1f, 0.2f, 0.3f}}));
}

TEST(FunctionSerializerTest, Nested) {
    EXPECT_EQ(
        "(grayscale-noise (x))",
        Serialize(pp::GrayscaleNoiseFunction(std::make_unique<pp::XFunction>())));

    EXPECT_EQ(
        "(inner-product (x) (y))",
        Serialize(pp::InnerProductFunction(
            std::make_unique<pp::XFunction>(),
            std::make_unique<pp::YFunction>())));

    EXPECT_EQ(
        "(dissolve (x) (y) (const 0.1 0.2 0.3))",
        Serialize(pp::DissolveFunction(
            std::make_unique<pp::XFunction>(),
            std::make_unique<pp::YFunction>(),
            std::make_unique<pp::ConstantFunction>(pp::Color{0.1f, 0.2f, 0.3f}))));
}
