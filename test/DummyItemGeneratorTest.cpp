#include <gtest/gtest.h>
#include "Generator/DummyItemGenerator.h"

TEST(DummyItemGeneratorTest, GenerateReturnsRequestedCount)
{
    DummyItemGenerator generator(42);

    auto items = generator.Generate(5, 1);

    EXPECT_EQ(items.size(), 5u);
}

TEST(DummyItemGeneratorTest, GenerateAssignsSequentialIdsStartingFromGivenId)
{
    DummyItemGenerator generator(42);

    auto items = generator.Generate(3, 10);

    EXPECT_EQ(items[0].id, 10);
    EXPECT_EQ(items[1].id, 11);
    EXPECT_EQ(items[2].id, 12);
}

TEST(DummyItemGeneratorTest, GenerateProducesPositiveQuantities)
{
    DummyItemGenerator generator(42);

    auto items = generator.Generate(20, 1);

    for (const auto& item : items)
    {
        EXPECT_GT(item.quantity, 0);
    }
}

TEST(DummyItemGeneratorTest, SameSeedProducesSameSequence)
{
    DummyItemGenerator generatorA(123);
    DummyItemGenerator generatorB(123);

    auto itemsA = generatorA.Generate(10, 1);
    auto itemsB = generatorB.Generate(10, 1);

    EXPECT_EQ(itemsA, itemsB);
}

TEST(DummyItemGeneratorTest, DifferentSeedsProduceDifferentQuantities)
{
    DummyItemGenerator generatorA(1);
    DummyItemGenerator generatorB(2);

    auto itemsA = generatorA.Generate(10, 1);
    auto itemsB = generatorB.Generate(10, 1);

    EXPECT_NE(itemsA, itemsB);
}
