#pragma once

#include <vector>
#include <set>

#include "stringfiable.h"
#include "state.h"
#include "glud.h"

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
