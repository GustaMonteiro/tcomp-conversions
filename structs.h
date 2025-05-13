#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>

#include "stringfiable.h"
#include "definitions.h"
#include "utils.h"

struct GLUD: public Stringfiable
{
    GLUD(std::set<char> variables, std::set<char> terminals, Productions productions, char start);

    std::string to_string() override;

    std::set<char> variables;
    std::set<char> terminals;
    Productions productions;
    char start;
};

struct AFND: public Stringfiable
{
    AFND(GLUD grammar);

    std::string to_string() override;

    std::set<char> states;
    std::set<char> alphabet;
    Transitions transitions;
    char start;
    std::set<char> final_states;
};

struct AFD: public Stringfiable
{
    AFD(AFND automata);

    std::string to_string() override;

    bool recognize_string(std::string input);
    AFD reverse();
    AFD complement();
};