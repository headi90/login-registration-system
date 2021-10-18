#include <gtest/gtest.h>
#include <string>
#include <utility>

#include "sha256PasswordHasher.hpp"

class Sha256TestFixture : public testing::TestWithParam<std::pair<std::string, std::string>> {
protected:
    Sha256PasswordHasher hasher{};
};

auto sha256TestParams = {
    std::make_pair(std::string{""}, std::string{"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"}),
    std::make_pair(std::string{"1"}, std::string{"6b86b273ff34fce19d6b804eff5a3f5747ada4eaa22f1d49c01e52ddb7875b4b"}),
    std::make_pair(std::string{"2"}, std::string{"d4735e3a265e16eee03f59718b9b5d03019c07d8b6c51f90da3a666eec13ab35"}),
    std::make_pair(std::string{"9"}, std::string{"19581e27de7ced00ff1ce50b2047e7a567c76b1cbaebabe5ef03f7c3017bb5b7"}),
    std::make_pair(std::string{"test"}, std::string{"9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08"}),
    std::make_pair(std::string{"TEST"}, std::string{"94ee059335e587e501cc4bf90613e0814f00a7b08bc7c648fd865a2af6a22cc2"}),
    std::make_pair(std::string{"ala"}, std::string{"5d530613969feac08946e337b5f3b1189b2f0b0ca73a812f4b83a504a0c773b2"}),
    std::make_pair(std::string{"alb"}, std::string{"6e226a9abab47f9e81f8afdffedc710ad333d76bd534b40f64d5f927a4e877b3"})};

INSTANTIATE_TEST_SUITE_P(sha256Hashes, Sha256TestFixture, testing::ValuesIn(sha256TestParams));

TEST_P(Sha256TestFixture, Sha256HasherCanHashStrings)
{
    auto testParam = GetParam();
    ASSERT_EQ(hasher.hash(testParam.first), testParam.second);
}
