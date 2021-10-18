#include "passwordValidator.hpp"
#include <algorithm>
#include <cctype>

constexpr size_t MinPasswordLength = 10;

ValidationResult PasswordValidator::validate(std::string& password)
{
    ValidationResult result = ValidationResult::OK;

    if (password.length() < MinPasswordLength) {
        result = ValidationResult::TooShort;
    }
    else if (std::none_of(password.cbegin(), password.cend(), [](auto ch) { return std::isdigit(ch); })) {
        result = ValidationResult::NoNumer;
    }
    else if (std::none_of(password.cbegin(), password.cend(), [](auto ch) { return std::ispunct(ch); })) {
        result = ValidationResult::NoSpecialCharacter;
    }
    else if (std::none_of(password.cbegin(), password.cend(), [](auto ch) { return std::isupper(ch); })) {
        result = ValidationResult::NoCapitalLetter;
    }
    else if (std::none_of(password.cbegin(), password.cend(), [](auto ch) { return std::islower(ch); })) {
        result = ValidationResult::NoSmallLetter;
    }
    return result;
}