#include "gtest/gtest.h"
#include "pp/expr/Generate.h"
#include "pp/fun/IFunction.h"
#include "pp/fun/Registry.h"
#include "pp/serialize/FunctionSerializer.h"

using pp::RandomExpression;
using pp::Registry;

TEST(GenerateTest, Basics) {
    Registry r;
    auto e = RandomExpression(r, pp::Range{});
    ASSERT_NE(nullptr, e);

    EXPECT_FALSE(Serialize(*e).empty());
}

