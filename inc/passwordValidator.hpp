#pragma once
#include "iPasswordValidator.hpp"

#include <string>

using ValidationResult = IPasswordValidator::PasswordValidatorResult;

class PasswordValidator : public IPasswordValidator {
public:
    ValidationResult validate(std::string& password) override;
};
