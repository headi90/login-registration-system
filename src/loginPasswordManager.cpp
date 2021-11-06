#include "loginPasswordManager.hpp"

LoginPasswordManager::LoginPasswordManager(iPasswordValidator* passwordValidator,
                                           iPasswordHasher* passwordHasher,
                                           iUserDatabaseHandler* userDatabaseHandler)
    : passwordValidator_(passwordValidator),
      passwordHasher_(passwordHasher),
      userDatabaseHandler_(userDatabaseHandler)
{
}

LoginPasswordManager::result LoginPasswordManager::registerNewUser(const std::string& login,
                                                                   const std::string& password,
                                                                   const std::string& passwordRepeated)
{
    (void)login;
    (void)password;
    (void)passwordRepeated;
    return result::OK;
}

LoginPasswordManager::result LoginPasswordManager::login(const std::string& login,
                                                         const std::string& password)
{
    if (!userDatabaseHandler_->checkIfUserExists(login)) {
        return result::UserDoesntExist;
    }

    User userToLogin = userDatabaseHandler_->read(login);

    std::string passwordHash = passwordHasher_->hash(password);

    if (userToLogin.getLogin() != login) {
        return result::WrongLogin;
    }

    if (userToLogin.getPasswordHash() != passwordHash) {
        return result::WrongPassword;
    }

    return result::OK;
}

LoginPasswordManager::result LoginPasswordManager::changePassword(const std::string& login,
                                                                  const std::string& password,
                                                                  const std::string& newPassword,
                                                                  const std::string& newPasswordRepeated)
{
    (void)login;
    (void)password;
    (void)newPassword;
    (void)newPasswordRepeated;
    return result::OK;
}