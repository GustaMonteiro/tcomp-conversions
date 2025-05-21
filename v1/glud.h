#pragma once

#include <set>

#include "stringfiable.h"
#include "definitions.h"

struct GLUD : public Stringfiable
{
    GLUD() = default;
    GLUD(std::set<char> variables, std::set<char> terminals, Productions productions, char start);

    std::string to_string() const override;

    std::set<char> variables;
    std::set<char> terminals;
    Productions productions;
    char start;
};
