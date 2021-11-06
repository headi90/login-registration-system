#pragma once
#include "iPasswordHasher.hpp"
#include "iPasswordValidator.hpp"
#include "iUserDatabaseHandler.hpp"

#include <string>

class LoginPasswordManager {
public:
    enum class result {
        OK,
        UserDoesntExist,
        WrongLogin,
        WrongPassword,
        Error
    };

    LoginPasswordManager(iPasswordValidator* passwordValidator,
                         iPasswordHasher* passwordHasher,
                         iUserDatabaseHandler* userDatabaseHandler);

    result registerNewUser(const std::string& login,
                           const std::string& password,
                           const std::string& passwordRepeated);

    result login(const std::string& login,
                 const std::string& password);

    result changePassword(const std::string& login,
                          const std::string& password,
                          const std::string& newPassword,
                          const std::string& newPasswordRepeated);

private:
    iPasswordValidator* passwordValidator_{};
    iPasswordHasher* passwordHasher_{};
    iUserDatabaseHandler* userDatabaseHandler_{};
};
