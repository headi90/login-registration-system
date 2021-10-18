#pragma once
#include <string>

class iPasswordHasher {
public:
    virtual std::string hash(std::string input) = 0;
    virtual ~iPasswordHasher();
};
