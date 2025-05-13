#pragma once

#include <vector>
#include <set>

#include "stringfiable.h"
#include "state.h"
#include "afnd.h"

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