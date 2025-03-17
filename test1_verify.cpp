#define BOOST_TEST_MODULE test_verify

#include <boost/test/unit_test.hpp>
#include "verify_lib.h"

BOOST_AUTO_TEST_SUITE(test_verify)

BOOST_AUTO_TEST_CASE(test_verify_all)
{
    // all ok
    const StringVector test_list1
    {
        "113.162.145	111	0",
        "157.39.22.224	5	6",
        "79.180.73.190	2	1"
    };

    for (const auto &item: test_list1)
        BOOST_CHECK(verify(split(item, '\t'), 3));

    // all invalid
    const StringVector test_list2
    {
        "179.210.145.4		0",
        "219.102.120.135	486",
        "219.102.120.46"
    };

    for (const auto &item: test_list2)
        BOOST_CHECK(!verify(split(item, '\t'), 3));

    // all parts ok
    const StringVector test_list3
    {
        "67.A.81.208",
        "85.254.10.1977",
        "23.240.215.189"
    };

    for (const auto &item: test_list3)
        BOOST_CHECK(verify(split(item, '.'), 4));

    // all parts invalid
    const StringVector test_list4
    {
        "46.70.1.",
        "46..215.189",
        "1.29."
    };

    for (const auto &item: test_list4)
        BOOST_CHECK(!verify(split(item, '.'), 4));

    // all bytes ok
    const StringVector test_list5
    {
        "1.2.3.4",
        "185.69.186.168",
        "110.152.103.161"
    };

    uint8_t byte;
    for (const auto &item: test_list5) {
        const auto addr = split(item, '.');
        if (verify(addr, 4))
            for (const auto &part: addr)
                BOOST_CHECK(verify(part, byte));
        else
            BOOST_CHECK(false);
    }

    // all bytes invalid
    const StringVector test_list6
    {
        "AA.182.81.131",
        "185.1820.81.131",
        "68.45.152.-1"
    };

    for (const auto &item: test_list6) {
        uint8_t byte;
        const auto addr = split(item, '.');
        if (verify(addr, 4)) {
            bool success = true;
            for (const auto &part: addr)
                success &= verify(part, byte);
            BOOST_CHECK(!success);
        } else
            BOOST_CHECK(false);
    }
}

BOOST_AUTO_TEST_SUITE_END()
