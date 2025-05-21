#include "state.h"

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
    return std::string();
}
