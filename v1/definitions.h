#pragma once

#include <vector>
#include <map>
#include <string>

#include "state.h"

constexpr char EMPTY = '#';
constexpr char EPSILON = '@';
const std::string EPSILON_STRING = "@";

struct Transition
{
    State origin;
    char symbol;
    State destination;
};

using Transitions = std::vector<Transition>;

using Productions = std::map<char, std::vector<std::string>>;
