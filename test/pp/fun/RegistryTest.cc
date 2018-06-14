#include "gtest/gtest.h"
#include "pp/fun/IFunctionGenerator.h"
#include "pp/fun/Registry.h"

using pp::Registry;

TEST(RegistryTest, Basics) {
    Registry r;
    auto f = r.GetRandom();
    ASSERT_NE(nullptr, f);
}
