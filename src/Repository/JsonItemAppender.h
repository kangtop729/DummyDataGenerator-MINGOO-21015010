#pragma once

#include <string>
#include "Repository/IItemAppender.h"

class JsonItemAppender : public IItemAppender
{
public:
    explicit JsonItemAppender(std::string filePath);

    std::vector<Item> FindAll() const override;
    void AppendAll(const std::vector<Item>& newItems) override;

private:
    std::string filePath;
};
