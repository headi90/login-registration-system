#include "user.hpp"

User::User(std::string login, std::string passwordHash)
    : login_(login), passwordHash_(passwordHash) {}
