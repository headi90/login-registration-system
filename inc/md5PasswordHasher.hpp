#pragma once
#include "iPasswordHasher.hpp"

class Md5PasswordHasher : public iPasswordHasher {
public:
    std::string hash(const std::string& input) override;
};
