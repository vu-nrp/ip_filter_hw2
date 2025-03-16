#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

//
using StringVector = std::vector<std::string>;

StringVector split(const std::string &str, char d)
{
    StringVector r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

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

int main(/*int argc, char const *argv[]*/)
{
    // std::cout << "Home Work #2" << std::endl;
    try {
        std::vector<std::pair<std::string, StringVector>> ip_pool_str;

        auto makePair = [](const std::string &str)
        {
            return std::make_pair(str, split(str, '.'));
        };

        // const StringVector debug_list
        // {
        //     "113.162.145.156	111	0",
        //     "157.39.22.224	5	6",
        //     "79.180.73.190	2	1",
        //     "179.210.145.4	22	0",
        //     "219.102.120.135	486	0",
        //     "219.102.120.46	486	0",
        //     "67.232.81.208	1	0",
        //     "85.254.10.197	0	7",
        //     "23.240.215.189	6	0",
        //     "46.70.1.189	6	0",
        //     "46.70.215.189	6	0",
        //     "1.29.168.152	17	0",
        //     "1.2.3.4	5	6",
        //     "185.69.186.168	1	3",
        //     "110.152.103.161	0	1",
        //     "185.182.81.131	1	1",
        //     "68.45.152.8	2	0"
        // };

        // read all input
        for (std::string line; std::getline(std::cin, line);) {
//        for (const auto &line: debug_list) {
            const auto addr_string = split(line, '\t');
            ip_pool_str.push_back(makePair(addr_string.at(0)));
        }

        int addrIndex = 0;
        AddressDataV4::Vector ip_pool_addr(ip_pool_str.size(), AddressDataV4 {"", {0}});

        // print all content & parse
//        std::cout << std::endl << "All ip's list" << std::endl;
        for (auto ip_string_it = ip_pool_str.cbegin(); ip_string_it != ip_pool_str.cend(); ++ip_string_it) {
            int partIndex = AddressDataV4::BytePartsCount;
            const auto ip_part_cbegin = ip_string_it->second.cbegin();

            ip_pool_addr[addrIndex].string = ip_string_it->first;
            for (auto ip_part_it = ip_part_cbegin; ip_part_it != ip_string_it->second.cend(); ++ip_part_it) {
                // parse
                try {
                    ip_pool_addr[addrIndex].address.byteParts[--partIndex] = std::stoul(*ip_part_it);
                } catch(...) {
                    std::cout << "invalid string to uint conversion for string " << ip_pool_addr[addrIndex].string;
                    break;
                }
            }

            // print all ip's list
            std::cout << ip_pool_addr[addrIndex].string << std::endl;

            ++addrIndex;
        }

//        std::cout << std::endl << "Sorting process";
        std::sort(std::begin(ip_pool_addr), std::end(ip_pool_addr), [](const auto &a, const auto &b)
        {
            // std::cout << std::endl;
            // std::cout << "compare as int: " << a.address.addr << " and " << b.address.addr << std::endl;
            // std::cout << "compare as str: " << a.string << " and " << b.string << std::endl;
            return (a.address.addr > b.address.addr);
        });

        // print all sorted
        // std::cout << std::endl << "All ip's sorted list" << std::endl;
        for (const auto &item: ip_pool_addr)
            std::cout << item.string << std::endl;

        // print 1st task (1st byte is 1)
        const uint8_t ByteValue01 {0x01};
        // std::cout << std::endl << "First byte is 1 in sorted list" << std::endl;
        for (const auto &item: ip_pool_addr)
            if (item.address.byteParts[3] == ByteValue01)
                std::cout << item.string << std::endl;

        // print 1st task (1st byte is 46, 2st byte is 70)
        const uint16_t WordValue {0x2E46};
        // std::cout << std::endl << "First byte is 46, second is 70 in sorted list" << std::endl;
        for (const auto &item: ip_pool_addr)
            if (item.address.wordParts[1] == WordValue)
                std::cout << item.string << std::endl;

        // print of any byte is 46
        const uint8_t ByteValue46 {0x2E};
        // std::cout << std::endl << "Any byte is 46 in sorted list" << std::endl;
        for (const auto &item: ip_pool_addr)
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
