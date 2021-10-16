#include <gtest/gtest.h>

#include "user.hpp"

TEST(UserTest, UserObjectCanBeCreated)
{
    User u{"testLogin", "1234567890"};
    ASSERT_EQ(u.getLogin(), "testLogin");
    ASSERT_EQ(u.getPasswordHash(), "1234567890");
}
