#include "DummyItemGenerator.h"

#include <random>

namespace
{
    constexpr int MinQuantity = 1;
    constexpr int MaxQuantity = 100;
}

DummyItemGenerator::DummyItemGenerator(unsigned int seed)
    : seed(seed)
{
}

std::vector<Item> DummyItemGenerator::Generate(int count, int startId) const
{
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> quantityDist(MinQuantity, MaxQuantity);

    std::vector<Item> items;
    items.reserve(count);
    for (int i = 0; i < count; ++i)
    {
        const int id = startId + i;
        items.push_back(Item{ id, "Item-" + std::to_string(id), quantityDist(rng) });
    }

    return items;
}
