#include <gtest/gtest.h>

#include "loginPasswordManager.hpp"
#include "mocks/mockPasswordHasher.hpp"
#include "mocks/mockPasswordValidator.hpp"
#include "mocks/mockUserDatabaseHandler.hpp"

using ::testing::Return;

class LoginPasswordManagerTest : public ::testing::Test {
protected:
    MockUserDatabaseHandler testDatabaseHandler{};
    MockPasswordHasher testPasswordHasher{};
    MockPasswordValidator testPasswordValidator{};
    LoginPasswordManager lpm = {&testPasswordValidator, &testPasswordHasher, &testDatabaseHandler};

    std::string testLogin = "testLogin";
    std::string testPass = "testPass";
    std::string testPassHash = "testPassHash";
};

TEST_F(LoginPasswordManagerTest, NotExistingUserCannotBeLogged)
{
    EXPECT_CALL(testDatabaseHandler, checkIfUserExists(testLogin))
        .WillOnce(Return(false));

    ASSERT_EQ(lpm.login(testLogin, testPass), LoginPasswordManager::result::UserDoesntExist);
}

TEST_F(LoginPasswordManagerTest, WrongLoginReturnedFromDatabase)
{
    EXPECT_CALL(testDatabaseHandler, checkIfUserExists(testLogin))
        .WillOnce(Return(true));

    EXPECT_CALL(testDatabaseHandler, read(testLogin))
        .WillOnce(Return(User{"wrongLogin", testPassHash}));

    EXPECT_CALL(testPasswordHasher, hash(testPass))
        .WillOnce(Return("wrongPass"));

    ASSERT_EQ(lpm.login(testLogin, testPass), LoginPasswordManager::result::WrongLogin);
}

TEST_F(LoginPasswordManagerTest, WrongPasswordHashResturnedFromDatabase)
{
    EXPECT_CALL(testDatabaseHandler, checkIfUserExists(testLogin))
        .WillOnce(Return(true));

    EXPECT_CALL(testDatabaseHandler, read(testLogin))
        .WillOnce(Return(User{testLogin, testPassHash}));

    EXPECT_CALL(testPasswordHasher, hash(testPass))
        .WillOnce(Return("wrongPass"));

    ASSERT_EQ(lpm.login(testLogin, testPass), LoginPasswordManager::result::WrongPassword);
}

TEST_F(LoginPasswordManagerTest, UserCanBeLogged)
{
    EXPECT_CALL(testDatabaseHandler, checkIfUserExists(testLogin))
        .WillOnce(Return(true));

    EXPECT_CALL(testDatabaseHandler, read(testLogin))
        .WillOnce(Return(User{testLogin, testPassHash}));

    EXPECT_CALL(testPasswordHasher, hash(testPass))
        .WillOnce(Return(testPassHash));

    ASSERT_EQ(lpm.login(testLogin, testPass), LoginPasswordManager::result::OK);
}
