#include "gtest/gtest.h"
#include "pp/expr/Breed.h"
#include "pp/fun/Registry.h"
#include "pp/serialize/FunctionParser.h"

TEST(BreedTest, Compatible) {
    pp::Registry registry;

    auto parent1 = pp::Parse("(mul (abs (x))     (div (x) (y)))", registry);
    auto parent2 = pp::Parse("(mul (div (y) (x)) (mul (x) (const -0.7 -0.7 -0.7)))", registry);

    ASSERT_NE(nullptr, parent1);
    ASSERT_NE(nullptr, parent2);

    auto child1 = pp::Breed(parent1, parent2, registry);
    ASSERT_NE(nullptr, child1);

    // TODO-jrk: inject random number generation so we can test deterministically.
}
