#include <gtest/gtest.h>
#include <string>
#include <utility>

#include "passwordValidator.hpp"

class PasswordValidatorTestFixture : public testing::TestWithParam<std::pair<std::string, ValidationResult>> {
protected:
    PasswordValidator validator{};
};

auto passwordValidateTestParams = {
    std::make_pair(std::string{"pass"}, ValidationResult::TooShort),
    std::make_pair(std::string{"p$sswordpass"}, ValidationResult::NoNumer),
    std::make_pair(std::string{"password1234567"}, ValidationResult::NoSpecialCharacter),
    std::make_pair(std::string{"password12345!@#"}, ValidationResult::NoCapitalLetter),
    std::make_pair(std::string{"PASSWORD12345!@#"}, ValidationResult::NoSmallLetter),
    std::make_pair(std::string{"QWERTY123456!@aa"}, ValidationResult::OK)};

INSTANTIATE_TEST_SUITE_P(passwordValidateTestParams, PasswordValidatorTestFixture, testing::ValuesIn(passwordValidateTestParams));

TEST_P(PasswordValidatorTestFixture, PasswordValidatorCanValidatePasswords)
{
    auto testParam = GetParam();
    ASSERT_EQ(validator.validate(testParam.first), testParam.second);
}
