#include <cassert>
#include <iostream>
#include <algorithm>
#include "verify_lib.h"
#include "ipfilter_types.h"


//!
//! \brief The AddressData class
//!
template<typename T>
struct AddressData
{
    using Vector = std::vector<AddressData>;
    static constexpr auto BytePartsCount {sizeof(T)};

    std::string string;
    union Address {
        T addr;
        uint8_t byteParts[BytePartsCount];
        uint16_t wordParts[BytePartsCount / 2];
    } address;
};

using AddressDataV4 = AddressData<uint32_t>;

int main()
{
    // std::cout << "Home Work #2" << std::endl;
    try {
        std::vector<std::pair<std::string, StringVector>> ip_pool_str;

        // read all input
        const auto LogPartsCount {3};
        for (std::string line; std::getline(std::cin, line);) {
            const auto log_string = split(line, '\t');
            if (verify(log_string, LogPartsCount)) {
                const auto addr_string = split(log_string.at(0), '.');
                if (verify(addr_string, AddressDataV4::BytePartsCount))
                    ip_pool_str.push_back(std::make_pair(log_string.at(0), addr_string));
            }
        }

        AddressDataV4::Vector ip_pool_addrs;
        ip_pool_addrs.reserve(ip_pool_str.size());

        // print all content & parse
        // std::cout << std::endl << "All ip's list" << std::endl;
        for (auto ip_string_it = ip_pool_str.cbegin(); ip_string_it != ip_pool_str.cend(); ++ip_string_it) {
            bool success = true;
            int partIndex = AddressDataV4::BytePartsCount;
            AddressDataV4 ip4data {ip_string_it->first, {0}};
            const auto ip_part_cbegin = ip_string_it->second.cbegin();

            for (auto ip_part_it = ip_part_cbegin; ip_part_it != ip_string_it->second.cend(); ++ip_part_it)
                if (verify(*ip_part_it, ip4data.address.byteParts[--partIndex])) {
                } else {
                    std::cout << "invalid string to uint conversion for string " << ip4data.string;
                    success = false;
                    break;
                }

            if (success) {
                //
                ip_pool_addrs.push_back(ip4data);

                // print all ip's list
                std::cout << ip4data.string << std::endl;
            }
        }

        // std::cout << std::endl << "Sorting process";
        std::sort(std::begin(ip_pool_addrs), std::end(ip_pool_addrs), [](const auto &a, const auto &b)
        {
            // std::cout << std::endl;
            // std::cout << "compare as int: " << a.address.addr << " and " << b.address.addr << std::endl;
            // std::cout << "compare as str: " << a.string << " and " << b.string << std::endl;
            return (a.address.addr > b.address.addr);
        });

        // print all sorted
        // std::cout << std::endl << "All ip's sorted list" << std::endl;
        for (const auto &item: ip_pool_addrs)
            std::cout << item.string << std::endl;

        // print 1st task (1st byte is 1)
        const uint8_t ByteValue01 {0x01};
        // std::cout << std::endl << "First byte is 1 in sorted list" << std::endl;
        for (const auto &item: ip_pool_addrs)
            if (item.address.byteParts[3] == ByteValue01)
                std::cout << item.string << std::endl;

        // print 1st task (1st byte is 46, 2st byte is 70)
        const uint16_t WordValue {0x2E46};
        // std::cout << std::endl << "First byte is 46, second is 70 in sorted list" << std::endl;
        for (const auto &item: ip_pool_addrs)
            if (item.address.wordParts[1] == WordValue)
                std::cout << item.string << std::endl;

        // print of any byte is 46
        const uint8_t ByteValue46 {0x2E};
        // std::cout << std::endl << "Any byte is 46 in sorted list" << std::endl;
        for (const auto &item: ip_pool_addrs)
            for (const auto &byte: item.address.byteParts)
                if (byte == ByteValue46) {
                    std::cout << item.string << std::endl;
                    break;
                }
    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
