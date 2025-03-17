#include "verify_lib.h"

bool verify(const StringVector &value, size_t expected)
{
    if (value.size() != expected)
        return false;

    for (const auto &item: value)
        if (item.empty())
            return false;

    return true;
}

bool verify(const std::string &ip_part, uint8_t &byte)
{
    bool result = false;
    try {
        const auto byteValue = std::stoul(ip_part);
        if ((byteValue >= 0) && (byteValue <= 255)) {
            byte = static_cast<uint8_t>(byteValue);
            result = true;
        }
    } catch(...) {
    }
    return result;
}
