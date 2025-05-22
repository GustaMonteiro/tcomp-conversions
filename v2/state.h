#pragma once

#include <set>
#include <string>

#include "printable.h"

struct State : public Printable
{
    State() = default;
    State(char name);
    State(std::string name);
    State(std::set<std::string> components);

    std::string to_string() const override;

    void operator+=(const State& s);

    std::set<std::string> components;
};

bool operator==(const State &left, const State &right);
bool operator!=(const State &left, const State &right);
bool operator<(const State &left, const State &right);
State operator+(const State &s1, const State &s2);