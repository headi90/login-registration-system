#pragma once
#include "iPasswordHasher.hpp"

class Md5PasswordHasher : public iPasswordHasher {
public:
    std::string hash(std::string& input) override;
};
