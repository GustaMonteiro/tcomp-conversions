#pragma once

#include <set>
#include <string>

#include "stringfiable.h"

struct State : public Stringfiable
{
    State() = default;
    State(char name, bool is_final_state = false);
    State(std::set<char> components, bool is_final_state = false);

    std::string to_string() const override;

    std::set<char> components;
    bool is_final_state = false;
};

bool operator==(const State &s1, const State &s2);
State operator+(const State &s1, const State &s2);
