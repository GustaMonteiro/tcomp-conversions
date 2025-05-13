#pragma once

#include <string>

struct Stringfiable
{
    virtual std::string to_string() = 0;
};