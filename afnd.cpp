#include <stack>
#include <sstream>

#include "afnd.h"
#include "utils.h"

AFND::AFND(GLUD grammar)
    : alphabet(grammar.terminals), start(grammar.start)
{
    for (auto variable : grammar.variables)
        this->states.emplace_back(variable);

    this->states.emplace_back('Z', true);

    this->final_states.push_back(&this->states.back());

    State *final_state = this->final_states.back();

    for (auto &[alpha, betas] : grammar.productions)
    {
        for (auto &beta : betas)
        {
            if (beta.size() == 1)
            {
                char character = beta[0];

                if (grammar.variables.contains(character))
                    this->transitions.emplace_back(alpha, EPSILON, character);
                else if (grammar.terminals.contains(character) || character == EPSILON)
                    this->transitions.emplace_back(alpha, character, *final_state);
            }
            else if (beta.size() == 2)
            {
                char terminal = beta[0];
                char variable = beta[1];

                this->transitions.emplace_back(alpha, terminal, variable);
            }
        }
    }
}

State AFND::epsilon_closure(State state) const
{
    std::set<char> visited;
    std::stack<char> to_visit;
    State closure = state;

    for (auto &component : state.components)
        to_visit.push(component);

    while (!to_visit.empty())
    {
        char current = to_visit.top();
        to_visit.pop();
        visited.insert(current);

        for (auto &transition : this->transitions)
        {
            if (transition.origin == current && transition.symbol == EPSILON)
            {
                closure = closure + transition.destination;

                for (auto &component : transition.destination.components)
                    if (!visited.contains(component))
                    {
                        to_visit.push(component);
                    }
            }
        }
    }

    return closure;
}

State AFND::transition(const State &origin, char symbol)
{
    State destination;

    for (auto &component : origin.components)
    {
        for (const auto &trans : this->transitions)
        {
            if (trans.origin == component && trans.symbol == symbol)
                destination = destination + trans.destination;
        }
    }

    if (!destination.components.size())
        return EMPTY;

    return destination;
}

std::string AFND::to_string() const
{
    std::stringstream ss;

    ss << vector_as_string(this->states, "Q") << '\n';
    ss << set_as_string(this->alphabet, "Sigma") << '\n';
    ss << transitions_as_string(this->transitions, "delta") << '\n';
    ss << "q0 = " << this->start << '\n';
    ss << vector_as_string(this->final_states, "F") << '\n';

    return ss.str();
}