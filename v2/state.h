#pragma once

#include <set>
#include <string>

#include "printable.h"

struct State: public Printable
{
    State() = default;
    State(std::string name);
    State(std::set<std::string> components);

    std::string to_string() const override;

    std::set<std::string> components;
};