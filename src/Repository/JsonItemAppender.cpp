#include "JsonItemAppender.h"

#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include "Serialization/ItemSerialization.h"

JsonItemAppender::JsonItemAppender(std::string filePath)
    : filePath(std::move(filePath))
{
}

std::vector<Item> JsonItemAppender::FindAll() const
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        return {};
    }

    nlohmann::json j;
    try
    {
        file >> j;
    }
    catch (const nlohmann::json::parse_error&)
    {
        throw std::runtime_error("Failed to parse JSON file: " + filePath);
    }

    return j.get<std::vector<Item>>();
}

void JsonItemAppender::AppendAll(const std::vector<Item>& newItems)
{
    auto items = FindAll();
    items.insert(items.end(), newItems.begin(), newItems.end());

    const nlohmann::json j = items;
    std::ofstream file(filePath);
    file << j.dump(2);
}
