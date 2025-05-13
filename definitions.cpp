#include "definitions.h"

#include <sstream>

#include "utils.h"

State::State(char name, bool is_final_state)
    : components{name}, is_final_state(is_final_state)
{
}

State::State(std::set<char> components, bool is_final_state)
    : components(components), is_final_state(is_final_state)
{
}

std::string State::to_string() const
{
    std::stringstream ss;

    if (this->components.size() == 1)
        ss << *components.begin();
    else
        ss << set_as_string(this->components);

    return ss.str();
}

bool operator==(const State &s1, const State &s2)
{
    return s1.components == s2.components;
}

State operator+(const State &s1, const State &s2)
{
    State sum = s1;

    for (auto &component : s2.components)
        sum.components.insert(component);

    return sum;
}
