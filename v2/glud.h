#pragma once

#include <set>
#include <string>
#include <vector>
#include <map>

#include "printable.h"

// GLUD = {V, T, P, S}
struct GLUD : public Printable
{
    GLUD(std::set<char> variables,
         std::set<char> terminals,
         std::map<char, std::vector<std::string>> productions,
         char start);

    std::string to_string() const override;

    std::set<char> variables;
    std::set<char> terminals;
    std::map<char, std::vector<std::string>> productions;
    char start;
};