#pragma once

#include "iUserDatabaseHandler.hpp"

#include <string>

class jsonUserDatabaseHandler : public iUserDatabaseHandler {
public:
    jsonUserDatabaseHandler(const std::string& jsonFileName);
    bool write(const User& user) override;
    User read(const std::string& login) override;
    bool remove(const std::string& login) override;

private:
    std::string jsonFileName_{};
};
