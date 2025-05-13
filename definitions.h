#pragma once

#include <vector>
#include <map>
#include <string>

#include "stringfiable.h"

struct State: public Stringfiable
{
    std::string to_string() const override;

    std::set<char> components;
};

struct Transition
{
    State origin;
    char symbol;
    State destination;
};

using Transitions = std::vector<Transition>;

using Productions = std::map<char, std::vector<std::string>>;
