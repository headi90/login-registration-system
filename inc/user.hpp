#pragma once
#include <string>

constexpr size_t secondsToPasswordExpire = 60;

class User {
public:
    User(std::string login, std::string passwordHash);

    std::string getLogin() const { return login_; };
    std::string getPasswordHash() const { return passwordHash_; };

private:
    std::string login_{};
    std::string passwordHash_{};
};
