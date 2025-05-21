#pragma once

#include <set>

#include "afnd.h"
#include "state.h"
#include "transition.h"
#include "printable.h"

struct AFND;

// AFD = {Q, Sigma, delta, q0, F}
// delta = (qi, a) -> qj  |  qi, qj E Q e a E Sigma
struct AFD: public Printable
{
    AFD() = default;
    AFD(AFND afnd);

    bool accept_string(std::string str) const;

    std::string to_string() const override;

    std::set<State> states;
    std::set<char> alphabet;
    std::set<Transition> transitions;
    State start;
    std::set<State> final_states;
};