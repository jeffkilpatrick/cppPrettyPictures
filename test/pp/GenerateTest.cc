#include "gtest/gtest.h"
#include "pp/Generate.h"
#include "pp/Registry.h"
#include "pp/fun/IFunction.h"
#include "pp/serialize/FunctionSerializer.h"

using pp::RandomExpression;
using pp::Registry;

TEST(GenerateTest, Basics) {
    Registry r;
    auto e = RandomExpression(r);
    ASSERT_NE(nullptr, e);

    EXPECT_FALSE(Serialize(*e).empty());
}

