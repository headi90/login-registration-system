#pragma once
#include <string>

class IPasswordValidator {
public:
    enum class PasswordValidatorResult {
        OK,
        TooShort,
        NoNumer,
        NoSpecialCharacter,
        NoCapitalLetter,
        NoSmallLetter
    };

    virtual PasswordValidatorResult validate(std::string& password) = 0;
    virtual ~IPasswordValidator() = default;
};
