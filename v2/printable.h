#pragma once

#include <string>
#include <ostream>

struct Printable
{
    virtual std::string to_string() const = 0;
};

std::ostream& operator<<(std::ostream& stream, const Printable& printable);