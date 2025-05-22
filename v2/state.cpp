#include <sstream>

#include "state.h"

State::State(char name)
    : components{{name}}
{
}

State::State(std::string name)
    : components{name}
{
}

State::State(std::set<std::string> components)
    : components(components)
{
}

std::string State::to_string() const
{
    std::stringstream ss;
    ss << this->components;
    return ss.str();
}

bool operator<(const State &left, const State &right)
{
    return left.components < right.components;
}
