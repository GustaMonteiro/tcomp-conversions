#include <sstream>
#include <iostream>

#include "afd.h"
#include "definitions.h"

static std::string create_state_with_index(size_t index)
{
    std::stringstream ss;
    ss << 'q' << index;
    return ss.str();
}

static void print_renaming_mapping(const std::map<State, State> &renaming_mapping)
{
    std::cout << ">> Renaming States:\n\n";

    for (auto &[before, after] : renaming_mapping)
        std::cout << before << " -> " << after << '\n';

    std::cout << '\n';
}


AFD::AFD(AFND afnd)
{
    *this = afnd.convert_to_deterministic();
}

/*
Input:  AFD = {Q', Sigma', delta', q0', F'}
            delta' = (q_i, a) -> q_j  |  q_i, q_j IN Q' and a IN Sigma'

Output: AFD_REV = {Q, Sigma, delta, q0, F}
            delta = (q_i, a) -> q_j  |  q_i, q_j IN Q and a IN Sigma

Process:
        Create an AFND with the following steps:

        1. Q = Q' U {Z}  =>  New initial state
        2. Sigma = Sigma'
        3. delta = (q_j, a) -> q_i FORALL (q_i, a) -> q_j IN delta'
                   U (Z, @) -> f  |  q_i, q_j IN Q' and f IN F'
        4. q0 = Z
        5. F = {q0'}
        
        To finish, convert the AFND to AFD.
*/
AFD AFD::reverse() const
{
    AFND to_reverse;

    to_reverse.states = this->states;
    to_reverse.states.insert('Z');

    to_reverse.alphabet = this->alphabet;

    // invert transitions
    for (auto &[origin, symbol, destination] : this->transitions)
        to_reverse.transitions.insert({destination, symbol, origin});

    // add inverted transitions from new state Z to the previous final states
    for (auto &final_state : this->final_states)
        to_reverse.transitions.insert({'Z', EPSILON_SYMBOL, final_state});

    to_reverse.start = 'Z';

    to_reverse.final_states.insert(this->start);

    return to_reverse.convert_to_deterministic();
}

/*
Input:  AFD = {Q', Sigma', delta', q0', F'}
            delta' = (q_i, a) -> q_j  |  q_i, q_j IN Q' and a IN Sigma'

Output: AFD_COMP = {Q, Sigma, delta, q0, F}
            delta = (q_i, a) -> q_j  |  q_i, q_j IN Q and a IN Sigma

Process:
        1. Q = Q'
        2. Sigma = Sigma'
        3. delta = delta'
        4. q0 = q0'
        5. F = {f | f NOTIN F'}
*/
AFD AFD::complement() const
{
    AFD complement;

    complement.states = this->states;
    complement.alphabet = this->alphabet;
    complement.transitions = this->transitions;
    complement.start = this->start;

    // each state that wasn't final will become final, and the ones that was final won't be anymore
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

void AFD::rename_states()
{
    std::map<State, State> renaming_mapping;

    size_t i = 0;

    for (auto &state : this->states)
        renaming_mapping.insert({state, create_state_with_index(i++)});

    // print_renaming_mapping(renaming_mapping);

    this->start = renaming_mapping[this->start];

    std::set<State> renamed_states;
    for (auto &state : this->states)
        renamed_states.insert(renaming_mapping[state]);
    this->states = renamed_states;

    std::set<State> renamed_final_states;
    for (auto &final_state : this->final_states)
        renamed_final_states.insert(renaming_mapping[final_state]);
    this->final_states = renamed_final_states;

    std::set<Transition> renamed_transitions;
    for (auto &[origin, symbol, destination] : this->transitions)
        renamed_transitions.insert({renaming_mapping[origin], symbol, renaming_mapping[destination]});
    this->transitions = renamed_transitions;
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
