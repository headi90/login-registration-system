#pragma once
#include <string>

constexpr size_t secondsToPasswordExpire = 60;

class User {
public:
    User(std::string login, std::string passwordHash);
    User() = default;

    std::string getLogin() const { return login_; };
    std::string getPasswordHash() const { return passwordHash_; };
    void setLogin(const std::string& login) { login_ = login; };
    void setPasswordHash(const std::string& passwordHash) { passwordHash_ = passwordHash; };

private:
    std::string login_{""};
    std::string passwordHash_{""};
};
