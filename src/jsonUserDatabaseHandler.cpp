#include "jsonUserDatabaseHandler.hpp"

bool jsonUserDatabaseHandler::write(const User& user)
{
    (void)user;
    return true;
}

User jsonUserDatabaseHandler::read(const std::string& login)
{
    (void)login;
    return User{"login", "pass"};
}

bool jsonUserDatabaseHandler::remove(const std::string& login)
{
    (void)login;
    return true;
}
