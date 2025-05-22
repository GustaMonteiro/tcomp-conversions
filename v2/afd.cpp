#include <sstream>

#include "afd.h"
#include "definitions.h"

AFD::AFD(AFND afnd)
{
    *this = afnd.convert_to_deterministic();
}

AFD AFD::reverse() const
{
    AFND to_reverse;

    to_reverse.states = this->states;
    to_reverse.states.insert('Z');

    to_reverse.alphabet = this->alphabet;

    for (auto &[origin, symbol, destination] : this->transitions)
        to_reverse.transitions.insert({destination, symbol, origin});

    for (auto &final_state : this->final_states)
        to_reverse.transitions.insert({'Z', EPSILON_SYMBOL, final_state});

    to_reverse.start = 'Z';

    to_reverse.final_states.insert(this->start);

    return to_reverse.convert_to_deterministic();
}

AFD AFD::complement() const
{
    AFD complement;

    complement.states = this->states;
    complement.alphabet = this->alphabet;
    complement.transitions = this->transitions;
    complement.start = this->start;

    for (auto &state : this->states)
        if (!this->is_final_state(state))
            complement.final_states.insert(state);

    return complement;
}

bool AFD::accept_string(std::string str) const
{
    State current_state = this->start;

    for (auto symbol : str)
        current_state = this->transition(current_state, symbol);

    return this->is_final_state(current_state);
}

bool AFD::contain_state(State state) const
{
    return this->states.find(state) != this->states.end();
}

State AFD::transition(State origin, char symbol) const
{
    for (const auto &transition : this->transitions)
    {
        if (transition.origin == origin && transition.symbol == symbol)
            return transition.destination;
    }

    return VOID_STATE;
}

bool AFD::is_final_state(State state) const
{
    return this->final_states.find(state) != this->final_states.end();
}

std::string AFD::to_string() const
{
    std::stringstream ss;

    ss << "Q = " << this->states << '\n';
    ss << "Sigma = " << this->alphabet << '\n';
    ss << "delta = " << this->transitions << '\n';
    ss << "q0 = " << this->start << '\n';
    ss << "F = " << this->final_states << '\n';

    return ss.str();
}
