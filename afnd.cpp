#include <sstream>
#include <queue>

#include "afnd.h"
#include "definitions.h"

AFND::AFND(GLUD grammar)
    : alphabet(grammar.terminals), start(grammar.start)
{
    for (auto &variable : grammar.variables)
        this->states.insert(variable);

    // Add new state that will be the final state
    State final_state('Z');
    this->states.insert(final_state);
    this->final_states.insert(final_state);

    for (auto &[alpha, betas] : grammar.productions)
    {
        for (auto &beta : betas)
        {
            if (beta.size() == 1)
            {
                char character = beta[0];

                if (grammar.is_variable(character))
                    this->transitions.insert({alpha, EPSILON_SYMBOL, character});
                else if (grammar.is_terminal(character) || character == EPSILON_SYMBOL)
                    this->transitions.insert({alpha, character, final_state});
            }
            else if (beta.size() == 2)
            {
                char terminal = beta[0];
                char variable = beta[1];

                this->transitions.insert({alpha, terminal, variable});
            }
        }
    }
}

AFND::AFND(AFD afd)
    : states(afd.states), alphabet(afd.alphabet), transitions(afd.transitions), start(afd.start), final_states(afd.final_states)
{
}

/*
Input:  AFND = {Q', Sigma', delta', q0', F'}
            delta' = (q_i, a) -> q_j  |  q_i, q_j IN Q' and a IN Sigma'

Output: AFD = {Q, Sigma, delta, q0, F}
            delta = (q_i, a) -> q_j  |  q_i, q_j IN Q and a IN Sigma

E(q) =  Epsilon Closure for State q. It is the set of reachable states
        starting from q using only Epsilon transitions
U(x) =  Union over all x

Process:
        1.  Q = P(Q') =>  All subsets of Q'
                Note:   the unreachable States won't be included in this
                        implementation, since it was done with a BFS
        2.  Sigma = Sigma'
        3.  delta = (S, a) -> E(U(delta'(s, a)) | S SUBSET Q, a IN Sigma, s IN S
        4.  q0 = E(q0')
        5.  F = {S IN Q | S INTERSECTION F' NOT EMPTY}
*/
AFD AFND::convert_to_deterministic() const
{
    AFD afd;

    afd.start = this->epsilon_closure(this->start);
    afd.alphabet = this->alphabet;

    // we'll be constructing the states gradually, starting from the start state
    afd.states.insert(afd.start);

    std::queue<State> to_visit;
    to_visit.push(afd.start);

    while (!to_visit.empty())
    {
        State current_state = to_visit.front();
        to_visit.pop();

        for (auto &component : current_state.components)
            if (this->final_states.find(component) != this->final_states.end())
                afd.final_states.insert(current_state);

        for (auto &symbol : this->alphabet)
        {
            // at this point, if no transition were found, the transition will return a state VOID,
            // where all undefined transitions will be directed
            State destination = this->transition(current_state, symbol);
            destination = this->epsilon_closure(destination);

            afd.transitions.insert({current_state, symbol, destination});

            if (!afd.contain_state(destination))
            {
                to_visit.push(destination);
                afd.states.insert(destination);
            }
        }
    }

    // rename all states to avoid dealing with very complex states
    afd.rename_states();

    return afd;
}

State AFND::epsilon_closure(State state) const
{
    State closure = state;

    for (auto &component : state.components)
    {
        for (auto &[origin, symbol, destination] : this->transitions)
        {
            if (origin == component && symbol == EPSILON_SYMBOL)
                closure += this->epsilon_closure(destination);
        }
    }

    return closure;
}

State AFND::transition(State origin, char symbol) const
{
    State destination;

    for (auto &component : origin.components)
    {
        for (auto &[transition_origin, transition_symbol, transition_destination] : this->transitions)
        {
            if (transition_origin == component && transition_symbol == symbol)
                destination += transition_destination;
        }
    }

    if (destination.components.empty())
        return VOID_STATE;

    return destination;
}

std::string AFND::to_string() const
{
    std::stringstream ss;

    ss << "Q = " << this->states << '\n';
    ss << "Sigma = " << this->alphabet << '\n';
    ss << "delta = " << this->transitions << '\n';
    ss << "q0 = " << this->start << '\n';
    ss << "F = " << this->final_states << '\n';

    return ss.str();
}