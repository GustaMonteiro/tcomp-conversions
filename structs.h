#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>

#include "stringfiable.h"
#include "definitions.h"
#include "utils.h"

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

struct AFND : public Stringfiable
{
    AFND() = default;
    AFND(GLUD grammar);

    State epsilon_closure(State state) const;

    State transition(const State &origin, char symbol);

    std::string to_string() const override;

    std::vector<State> states;
    std::set<char> alphabet;
    Transitions transitions;
    State start;
    std::vector<State *> final_states;
};

struct AFD : public Stringfiable
{
    AFD() = default;
    AFD(AFND automata);

    std::string to_string() const override;

    bool recognize_string(std::string input);
    AFD reverse();
    AFD complement();

    std::vector<State> states;
    std::set<char> alphabet;
    Transitions transitions;
    State start;
    std::vector<State *> final_states;

private:
    State transition(const State &origin, char symbol);
};