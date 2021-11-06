#include <gmock/gmock.h>

#include "iUserDatabaseHandler.hpp"

class MockUserDatabaseHandler : public iUserDatabaseHandler {
public:
    MOCK_METHOD(bool, write, (const User& user), (override));
    MOCK_METHOD(User, read, (const std::string& login), (override));
    MOCK_METHOD(bool, remove, (const std::string& login), (override));
    MOCK_METHOD(bool, checkIfUserExists, (const std::string& login), (override));
};
