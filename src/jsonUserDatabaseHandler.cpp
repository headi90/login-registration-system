#include "jsonUserDatabaseHandler.hpp"

#include "nlohmann/json.hpp"

#include <fstream>
#include <iostream>

using json = nlohmann::json;

jsonUserDatabaseHandler::jsonUserDatabaseHandler(const std::string& jsonFileName)
    : jsonFileName_(jsonFileName)
{
}

bool jsonUserDatabaseHandler::write(const User& user)
{
    std::ifstream jsonFile(jsonFileName_);
    json jsonHandler;
    if (jsonFile.is_open()) {
        jsonFile >> jsonHandler;
        jsonFile.close();
    }
    else {
        // File doesn't exist, so have to be created from the scratch
        jsonHandler["users"] = {};
    }

    jsonHandler["users"].push_back({{"login", user.getLogin()}, {"password", user.getPasswordHash()}});

    std::ofstream jsonFileOut(jsonFileName_, std::ios::out | std::ios::trunc);
    if (jsonFileOut.is_open()) {
        jsonFileOut << jsonHandler.dump(4);
        jsonFileOut.close();
        return true;
    }
    return false;
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
