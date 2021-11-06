#include <gmock/gmock.h>

#include "iPasswordValidator.hpp"

class MockPasswordValidator : public iPasswordValidator {
public:
    MOCK_METHOD(PasswordValidatorResult, validate, (std::string & password), (override));
};
