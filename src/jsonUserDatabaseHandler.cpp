#include "jsonUserDatabaseHandler.hpp"

#include <fstream>
#include <iostream>

jsonUserDatabaseHandler::jsonUserDatabaseHandler(const std::string& jsonFileName)
    : jsonFileName_(jsonFileName)
{
}

bool jsonUserDatabaseHandler::write(const User& user)
{
    if (checkIfUserExists(user.getLogin())) {
        return false;
    }

    json jsonHandler;
    if (!readJsonFromFile(jsonHandler)) {
        // File doesn't exist, so have to be created from the scratch
        jsonHandler["users"] = {};
    }

    jsonHandler["users"].push_back({{"login", user.getLogin()}, {"password", user.getPasswordHash()}});

    return writeJsonToFile(jsonHandler);
}

User jsonUserDatabaseHandler::read(const std::string& login)
{
    User userReturn{};
    json jsonHandler;
    if (readJsonFromFile(jsonHandler)) {
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
    if (!checkIfUserExists(login)) {
        return true;
    }

    json jsonHandler;
    if (!readJsonFromFile(jsonHandler)) {
        // File doesn't exist, so nothing to do
        return true;
    }

    auto iter = jsonHandler["users"].begin();
    for (; iter != jsonHandler["users"].end(); iter++) {
        if ((*iter)["login"].get<std::string>() == login) {
            jsonHandler["users"].erase(iter);
            return writeJsonToFile(jsonHandler);
        }
    }
    return false;
}

bool jsonUserDatabaseHandler::checkIfUserExists(const std::string& login)
{
    json jsonHandler;
    if (readJsonFromFile(jsonHandler)) {
        for (auto& elem : jsonHandler["users"]) {
            if (elem["login"].get<std::string>() == login) {
                return true;
            }
        }
    }
    return false;
}

bool jsonUserDatabaseHandler::writeJsonToFile(json& jsonHandler)
{
    std::ofstream jsonFileOut(jsonFileName_, std::ios::out | std::ios::trunc);
    if (jsonFileOut.is_open()) {
        jsonFileOut << jsonHandler.dump(4);
        jsonFileOut.close();
        return true;
    }
    return false;
}

bool jsonUserDatabaseHandler::readJsonFromFile(json& jsonHandler)
{
    std::ifstream inputJsonFile(jsonFileName_);
    if (inputJsonFile.is_open()) {
        inputJsonFile >> jsonHandler;
        inputJsonFile.close();
        return true;
    }
    return false;
}
