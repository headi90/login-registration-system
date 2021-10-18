#include <gtest/gtest.h>

#include <string>
#include <utility>
#include "md5PasswordHasher.hpp"

class Md5TestFixture : public testing::TestWithParam<std::pair<std::string, std::string>> {
protected:
    Md5PasswordHasher hasher{};
};

auto md5TestParams = {
    std::make_pair(std::string{""}, std::string{"d41d8cd98f00b204e9800998ecf8427e"}),
    std::make_pair(std::string{"1"}, std::string{"c4ca4238a0b923820dcc509a6f75849b"}),
    std::make_pair(std::string{"2"}, std::string{"c81e728d9d4c2f636f067f89cc14862c"}),
    std::make_pair(std::string{"9"}, std::string{"45c48cce2e2d7fbdea1afc51c7c6ad26"}),
    std::make_pair(std::string{"test"}, std::string{"098f6bcd4621d373cade4e832627b4f6"}),
    std::make_pair(std::string{"TEST"}, std::string{"033bd94b1168d7e4f0d644c3c95e35bf"}),
    std::make_pair(std::string{"ala"}, std::string{"e88e6128e26eeff4daf1f5db07372784"}),
    std::make_pair(std::string{"alb"}, std::string{"73717aafac1e7701dab0fa02b8936926"})};

INSTANTIATE_TEST_SUITE_P(md5Hashes, Md5TestFixture, testing::ValuesIn(md5TestParams));

TEST_P(Md5TestFixture, md5HasherCanHashStrings)
{
    auto testParam = GetParam();
    ASSERT_EQ(hasher.hash(testParam.first), testParam.second);
}
