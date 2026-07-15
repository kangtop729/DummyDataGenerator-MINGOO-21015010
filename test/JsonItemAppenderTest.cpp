#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include "Repository/JsonItemAppender.h"

namespace
{
    std::filesystem::path MakeTempFilePath()
    {
        return std::filesystem::temp_directory_path() / "DummyDataGeneratorTest_items.json";
    }
}

class JsonItemAppenderTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        filePath = MakeTempFilePath().string();
        std::filesystem::remove(filePath);
    }

    void TearDown() override
    {
        std::filesystem::remove(filePath);
    }

    std::string filePath;
};

TEST_F(JsonItemAppenderTest, FindAllOnMissingFileReturnsEmptyList)
{
    JsonItemAppender appender(filePath);

    EXPECT_TRUE(appender.FindAll().empty());
}

TEST_F(JsonItemAppenderTest, AppendAllOnMissingFileCreatesFileWithNewItems)
{
    JsonItemAppender appender(filePath);

    appender.AppendAll({ Item{ 1, "Widget", 10 }, Item{ 2, "Gadget", 3 } });

    auto items = appender.FindAll();
    ASSERT_EQ(items.size(), 2u);
    EXPECT_EQ(items[0], (Item{ 1, "Widget", 10 }));
    EXPECT_EQ(items[1], (Item{ 2, "Gadget", 3 }));
}

TEST_F(JsonItemAppenderTest, AppendAllPreservesExistingDataAndAddsNew)
{
    JsonItemAppender appender(filePath);
    appender.AppendAll({ Item{ 1, "Widget", 10 } });

    appender.AppendAll({ Item{ 2, "Gadget", 3 } });

    auto items = appender.FindAll();
    ASSERT_EQ(items.size(), 2u);
    EXPECT_EQ(items[0], (Item{ 1, "Widget", 10 }));
    EXPECT_EQ(items[1], (Item{ 2, "Gadget", 3 }));
}

TEST_F(JsonItemAppenderTest, LoadingCorruptedFileThrows)
{
    {
        std::ofstream file(filePath);
        file << "{ not valid json ";
    }

    JsonItemAppender appender(filePath);

    EXPECT_THROW(appender.FindAll(), std::runtime_error);
}
