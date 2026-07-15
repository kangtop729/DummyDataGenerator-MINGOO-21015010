#pragma once

#include <vector>
#include "Model/Item.h"

class DummyItemGenerator
{
public:
    explicit DummyItemGenerator(unsigned int seed);

    std::vector<Item> Generate(int count, int startId) const;

private:
    unsigned int seed;
};
