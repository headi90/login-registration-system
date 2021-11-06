#include <gmock/gmock.h>

#include "iPasswordHasher.hpp"

class MockPasswordHasher : public iPasswordHasher {
public:
    MOCK_METHOD(std::string, hash, (const std::string& input), (override));
};
