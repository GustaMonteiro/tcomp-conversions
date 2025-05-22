#include <sstream>

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
{
}

AFD AFND::convert_to_deterministic() const
{
    return AFD();
}

State AFND::epsilon_closure(State state) const
{
    return State();
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