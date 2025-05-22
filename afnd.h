#pragma once

#include <set>

#include "glud.h"
#include "state.h"
#include "transition.h"
#include "afd.h"
#include "printable.h"

struct AFD;

// AFND = {Q, Sigma, delta, q0, F}
// delta = (qi, a) -> qj  |  qi, qj E Q e a E Sigma
struct AFND: public Printable
{
    AFND() = default;
    AFND(GLUD grammar);
    AFND(AFD afd);

    AFD convert_to_deterministic() const;
    State epsilon_closure(State state) const;
    State transition(State origin, char symbol) const;

    std::string to_string() const override;

    std::set<State> states;
    std::set<char> alphabet;
    std::set<Transition> transitions;
    State start;
    std::set<State> final_states;
};