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
    const std::string jsonDummyContent{"{\n    \"users\": [\n        {\n            \"login\": \"john\",\n            \"password\": \"12345678\"\n        },\n        {\n            \"login\": \"anthony\",\n            \"password\": \"qwerty\"\n        }\n    ]\n}\n"};
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

TEST_F(JsonDatabaseHandlerTest, JsonFileCanBeAppended)
{
    jsonUserDatabaseHandler jsonHandlerUnderTest{testFileNameAbsolute};
    auto returnVal = jsonHandlerUnderTest.write(User{"Kate", "testPass"});
    EXPECT_TRUE(returnVal);

    auto userOut = jsonHandlerUnderTest.read("Kate");
    EXPECT_EQ(userOut.getLogin(), "Kate");
    EXPECT_EQ(userOut.getPasswordHash(), "testPass");

    jsonUserDatabaseHandler jsonHandlerUnderTest2{testFileNameAbsolute};
    auto userOut2 = jsonHandlerUnderTest2.read("Kate");
    EXPECT_EQ(userOut2.getLogin(), "Kate");
    EXPECT_EQ(userOut2.getPasswordHash(), "testPass");
}

TEST_F(JsonDatabaseHandlerTest, JsonFileCanBeCreated)
{
    const std::string testFileNameThatDoesntExist{"thisFileDoesntExist.json"};

    jsonUserDatabaseHandler jsonHandlerUnderTest{testFileNameThatDoesntExist};
    auto returnVal = jsonHandlerUnderTest.write(User{"Kate", "testPass"});
    EXPECT_TRUE(returnVal);

    auto userOut = jsonHandlerUnderTest.read("Kate");
    EXPECT_EQ(userOut.getLogin(), "Kate");
    EXPECT_EQ(userOut.getPasswordHash(), "testPass");

    jsonUserDatabaseHandler jsonHandlerUnderTest2{testFileNameThatDoesntExist};
    auto userOut2 = jsonHandlerUnderTest2.read("Kate");
    EXPECT_EQ(userOut2.getLogin(), "Kate");
    EXPECT_EQ(userOut2.getPasswordHash(), "testPass");

    // Remove temp file
    std::filesystem::remove(testFileNameThatDoesntExist);
}
