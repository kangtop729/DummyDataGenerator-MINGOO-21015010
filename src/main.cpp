#ifdef _DEBUG
#include <gtest/gtest.h>
#else
#include <iostream>
#include <random>
#include "Model/Item.h"
#include "Repository/JsonItemAppender.h"
#include "Generator/DummyItemGenerator.h"

namespace
{
    int NextId(const std::vector<Item>& items)
    {
        int maxId = 0;
        for (const auto& item : items)
        {
            maxId = std::max(maxId, item.id);
        }
        return maxId + 1;
    }
}
#endif

int main(int argc, char** argv)
{
#ifdef _DEBUG
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    JsonItemAppender appender("items.json");

    std::cout << "DummyDataGenerator PoC\n";
    std::cout << "How many dummy items to generate? ";

    int count = 0;
    if (!(std::cin >> count) || count <= 0)
    {
        std::cout << "Invalid count.\n";
        return 1;
    }

    const auto existing = appender.FindAll();
    const int startId = NextId(existing);

    std::random_device rd;
    const DummyItemGenerator generator(rd());
    const auto newItems = generator.Generate(count, startId);

    appender.AppendAll(newItems);

    std::cout << "Generated " << newItems.size() << " items (id " << startId
               << " to " << (startId + count - 1) << ").\n";
    std::cout << "Total items now: " << (existing.size() + newItems.size()) << "\n";

    return 0;
#endif
}
