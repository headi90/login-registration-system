#pragma once

#include "iUserDatabaseHandler.hpp"

#include "nlohmann/json.hpp"

#include <string>

using json = nlohmann::json;
class jsonUserDatabaseHandler : public iUserDatabaseHandler {
public:
    jsonUserDatabaseHandler(const std::string& jsonFileName);
    bool write(const User& user) override;
    User read(const std::string& login) override;
    bool remove(const std::string& login) override;

private:
    std::string jsonFileName_{};

    bool checkIfUserExists(const std::string& login);
    bool writeJsonToFile(json& jsonHandler);
    bool readJsonFromFile(json& jsonHandler);
};
