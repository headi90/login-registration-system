#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>

#include "jsonUserDatabaseHandler.hpp"
#include "user.hpp"

class JsonDatabaseHandlerTest : public ::testing::Test {
protected:
    std::string testFileNameAbsolute{};

    void SetUp() override
    {
        std::ofstream testFile(testFileName);
        testFile << jsonDummyContent;
        testFile.close();

        std::filesystem::path p = testFileName;
        testFileNameAbsolute = std::filesystem::absolute(p);
    }

    void TearDown() override
    {
        std::filesystem::remove(testFileName);
    }

private:
    const std::string jsonDummyContent{"{\n\t\"users\": [\n\t\t{\n\t\t\t\"login\": \"john\",\n\t\t\t\"password\": \"12345678\"\n\t\t},\n\t\t{\n\t\t\t\"login\": \"anthony\",\n\t\t\t\"password\": \"qwerty\"\n\t\t}\n\t]\n}\n"};
    const std::string testFileName{"test.json"};
};

TEST_F(JsonDatabaseHandlerTest, JsonFileCanBeRead)
{
    jsonUserDatabaseHandler jsonHandlerUnderTest{testFileNameAbsolute};
    auto userOut = jsonHandlerUnderTest.read("john");
    EXPECT_EQ(userOut.getLogin(), "john");
    EXPECT_EQ(userOut.getPasswordHash(), "12345678");

    auto userOut2 = jsonHandlerUnderTest.read("anthony");
    EXPECT_EQ(userOut2.getLogin(), "anthony");
    EXPECT_EQ(userOut2.getPasswordHash(), "qwerty");
}

TEST_F(JsonDatabaseHandlerTest, NonExistingLoginCanBeHandled)
{
    jsonUserDatabaseHandler jsonHandlerUnderTest{testFileNameAbsolute};
    auto userOut = jsonHandlerUnderTest.read("Jonny");
    EXPECT_EQ(userOut.getLogin(), "");
    EXPECT_EQ(userOut.getPasswordHash(), "");
}

TEST_F(JsonDatabaseHandlerTest, NonExistingFileCanBeHandled)
{
    jsonUserDatabaseHandler jsonHandlerUnderTest{"thisFileDoesntExist.json"};
    auto userOut = jsonHandlerUnderTest.read("john");
    EXPECT_EQ(userOut.getLogin(), "");
    EXPECT_EQ(userOut.getPasswordHash(), "");
}
