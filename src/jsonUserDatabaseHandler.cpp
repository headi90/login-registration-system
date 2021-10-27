#include "jsonUserDatabaseHandler.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

jsonUserDatabaseHandler::jsonUserDatabaseHandler(const std::string& jsonFileName)
    : jsonFileName_(jsonFileName)
{
}

bool jsonUserDatabaseHandler::write(const User& user)
{
    (void)user;
    return true;
}

User jsonUserDatabaseHandler::read(const std::string& login)
{
    User userReturn{};
    std::ifstream inputJsonFile(jsonFileName_);
    if (inputJsonFile.is_open()) {
        json jsonHandler;
        inputJsonFile >> jsonHandler;
        inputJsonFile.close();

        for (auto& elem : jsonHandler["users"]) {
            if (elem["login"].get<std::string>() == login) {
                userReturn.setLogin(login);
                userReturn.setPasswordHash(elem["password"].get<std::string>());
                break;
            }
        }
    }

    return userReturn;
}

bool jsonUserDatabaseHandler::remove(const std::string& login)
{
    (void)login;
    return true;
}
