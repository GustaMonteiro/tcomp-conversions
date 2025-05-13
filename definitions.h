#pragma once

#include <vector>
#include <map>
#include <string>
#include <set>

#include "stringfiable.h"

constexpr char EMPTY = '#';
constexpr char EPSILON = '@';
const std::string EPSILON_STRING = "@";

struct State : public Stringfiable
{
    State() = default;
    State(char name, bool is_final_state = false);
    State(std::set<char> components, bool is_final_state = false);

    std::string to_string() const override;

    std::set<char> components;
    bool is_final_state = false;
};

struct Transition
{
    State origin;
    char symbol;
    State destination;
};

bool operator==(const State &s1, const State &s2);
State operator+(const State &s1, const State &s2);

using Transitions = std::vector<Transition>;

using Productions = std::map<char, std::vector<std::string>>;
