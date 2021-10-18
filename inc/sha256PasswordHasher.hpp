#pragma once
#include "iPasswordHasher.hpp"

class Sha256PasswordHasher : public iPasswordHasher {
public:
    std::string hash(std::string& input) override;
};
