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

void State::operator+=(const State &s)
{
    this->components.insert(s.components.begin(), s.components.end());
}

bool operator==(const State &left, const State &right)
{
    return left.components == right.components;
}

bool operator!=(const State &left, const State &right)
{
    return !(left == right);
}

bool operator<(const State &left, const State &right)
{
    return left.components < right.components;
}

State operator+(const State &s1, const State &s2)
{
    State sum = s1;
    sum.components.insert(s2.components.begin(), s2.components.end());
    return sum;
}
