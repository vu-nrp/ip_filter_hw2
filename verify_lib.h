#pragma once

#include <stdint.h>
#include "ipfilter_types.h"

bool verify(const StringVector &value, size_t expected);

bool verify(const std::string &ip_part, uint8_t &byte);
