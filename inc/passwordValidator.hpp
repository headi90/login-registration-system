#pragma once
#include "iPasswordValidator.hpp"

#include <string>

using ValidationResult = iPasswordValidator::PasswordValidatorResult;

class PasswordValidator : public iPasswordValidator {
public:
    ValidationResult validate(std::string& password) override;
};
