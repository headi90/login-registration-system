#include <gtest/gtest.h>

#include "md5PasswordHasher.hpp"

TEST(Md5Tests, Md5HasherCanHashSimpleStrings)
{
    Md5PasswordHasher hasher{};
    ASSERT_EQ(hasher.hash("1"), "c4ca4238a0b923820dcc509a6f75849b");
    ASSERT_EQ(hasher.hash("2"), "c81e728d9d4c2f636f067f89cc14862c");
    ASSERT_EQ(hasher.hash("9"), "45c48cce2e2d7fbdea1afc51c7c6ad26");
    ASSERT_EQ(hasher.hash("test"), "098f6bcd4621d373cade4e832627b4f6");
    ASSERT_EQ(hasher.hash("TEST"), "033bd94b1168d7e4f0d644c3c95e35bf");
    ASSERT_EQ(hasher.hash("ala"), "e88e6128e26eeff4daf1f5db07372784");
    ASSERT_EQ(hasher.hash("alb"), "73717aafac1e7701dab0fa02b8936926");
}
