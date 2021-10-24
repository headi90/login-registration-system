#pragma once

#include "iUserDatabaseHandler.hpp"

class jsonUserDatabaseHandler : public iUserDatabaseHandler {
public:
    bool write(const User& user) override;
    User read(const std::string& login) override;
    bool remove(const std::string& login) override;
};
