#pragma once

#include <vector>
#include "Model/Item.h"

class IItemAppender
{
public:
    virtual ~IItemAppender() = default;

    virtual std::vector<Item> FindAll() const = 0;
    virtual void AppendAll(const std::vector<Item>& newItems) = 0;
};
