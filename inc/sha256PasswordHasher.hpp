#pragma once
#include "iPasswordHasher.hpp"

class Sha256PasswordHasher : public iPasswordHasher {
public:
    std::string hash(const std::string& input) override;
};
