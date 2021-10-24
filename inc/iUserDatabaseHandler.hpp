#pragma once
#include <string>
#include "user.hpp"

class iUserDatabaseHandler {
public:
    virtual bool write(const User& user) = 0;
    virtual User read(const std::string& login) = 0;
    virtual bool remove(const std::string& login) = 0;
};
