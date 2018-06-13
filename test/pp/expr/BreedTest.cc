#include "gtest/gtest.h"
#include "pp/expr/Breed.h"
#include "pp/fun/Registry.h"
#include "pp/serialize/FunctionParser.h"
#include "pp/utility/Random.h"

class Deterministic : public pp::IRandom {
public:
    Deterministic(std::vector<IRandom::result_type>&& results)
        : m_results(std::move(results))
    {
        if (m_results.empty())
        {
            throw std::invalid_argument("Need at least one result to return");
        }
    }

    IRandom::result_type operator()() override
    {
        if (m_currentIdx >= m_results.size())
        {
            throw std::logic_error("out of random results");
        }

        return m_results[m_currentIdx++];
    }

private:
    size_t m_currentIdx{0};
    std::vector<IRandom::result_type> m_results;
};

TEST(BreedTest, Compatible) {
    pp::Registry registry;

    auto parent1 = pp::Parse("(mul (abs (x))     (div (x) (y)))", registry);
    auto parent2 = pp::Parse("(mul (div (y) (x)) (mul (x) (const -0.7 -0.7 -0.7)))", registry);

    ASSERT_NE(nullptr, parent1);
    ASSERT_NE(nullptr, parent2);

    {
        // Pick left arg every time
        Deterministic random({0, 0});
        auto child = pp::Breed(parent1, parent2, registry, random);
        ASSERT_NE(nullptr, child);
        EXPECT_TRUE(child->Equals(*parent1));
    }

    {
        // Pick right arg every time
        Deterministic random({1, 1});
        auto child = pp::Breed(parent1, parent2, registry, random);
        ASSERT_NE(nullptr, child);
        EXPECT_TRUE(child->Equals(*parent2));
    }

    {
        // Left, then right
        Deterministic random({0, 1});
        auto child = pp::Breed(parent1, parent2, registry, random);
        ASSERT_NE(nullptr, child);
        auto expected = pp::Parse("(mul (abs (x)) (mul (x) (const -0.7 -0.7 -0.7)))", registry);
        ASSERT_NE(nullptr, expected);
        EXPECT_TRUE(child->Equals(*expected));
    }

    {
        // Right, then left
        Deterministic random({1, 0});
        auto child = pp::Breed(parent1, parent2, registry, random);
        ASSERT_NE(nullptr, child);
        auto expected = pp::Parse("(mul (div (y) (x)) (div (x) (y)))", registry);
        ASSERT_NE(nullptr, expected);
        EXPECT_TRUE(child->Equals(*expected));
    }
}
