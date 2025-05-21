#pragma once

#include <string>
#include <ostream>
#include <set>
#include <map>
#include <vector>

struct State;
struct Transition;

struct Printable
{
    virtual std::string to_string() const = 0;
};

std::ostream& operator<<(std::ostream& stream, const Printable& printable);
std::ostream& operator<<(std::ostream& stream, const std::set<State>& printables);
std::ostream& operator<<(std::ostream& stream, const std::set<Transition>& transitions);
std::ostream& operator<<(std::ostream& stream, const std::set<char>& set);
std::ostream& operator<<(std::ostream& stream, const std::map<char, std::vector<std::string>>& set);