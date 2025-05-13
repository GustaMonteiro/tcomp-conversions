#include <sstream>
#include <stack>

#include "structs.h"
#include "utils.h"

GLUD::GLUD(std::set<char> variables, std::set<char> terminals, Productions productions, char start)
    : variables(variables), terminals(terminals), productions(productions), start(start)
{
}

std::string GLUD::to_string() const
{
    std::stringstream ss;

    ss << set_as_string(this->variables, "V") << '\n';
    ss << set_as_string(this->terminals, "T") << '\n';
    ss << productions_as_string(this->productions, "P") << '\n';
    ss << "S = " << this->start << '\n';

    return ss.str();
}

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

static bool is_state_in_vector(State state, const std::vector<State> &states)
{
    for (auto &st : states)
        if (st == state)
            return true;

    return false;
}

AFD::AFD(AFND automata)
    : alphabet(automata.alphabet)
{
    this->start = automata.epsilon_closure(automata.start);

    this->states.push_back(this->start);
    this->states.push_back(EMPTY);

    for (int i = 0; i < this->states.size(); i++)
    {
        for (auto symbol : this->alphabet)
        {
            State destination = automata.transition(this->states[i], symbol);
            State destination_closure = automata.epsilon_closure(destination);
            if (!is_state_in_vector(destination_closure, this->states))
                this->states.push_back(destination_closure);

            this->transitions.emplace_back(this->states[i], symbol, destination_closure);
        }
    }

    for (auto &state : this->states)
    {
        if (state.components.contains(*automata.final_states.back()->components.begin()))
        {
            this->final_states.push_back(&state);
            state.is_final_state = true;
        }
    }
}

std::string AFD::to_string() const
{
    std::stringstream ss;

    ss << vector_as_string(this->states, "Q") << '\n';
    ss << set_as_string(this->alphabet, "Sigma") << '\n';
    ss << transitions_as_string(this->transitions, "delta") << '\n';
    ss << "q0 = " << this->start << '\n';
    ss << vector_as_string(this->final_states, "F") << '\n';

    return ss.str();
}

bool AFD::recognize_string(std::string input)
{
    State current_state = this->start;

    for (auto symbol : input)
        current_state = this->transition(current_state, symbol);

    for (auto final_state : this->final_states)
        if (current_state == *final_state)
            return true;

    return false;
}

AFD AFD::reverse()
{
    return AFD();
}

AFD AFD::complement()
{
    return AFD();
}

State AFD::transition(const State &origin, char symbol)
{
    for (const auto &trans : this->transitions)
    {
        if (trans.origin == origin && trans.symbol == symbol)
            return trans.destination;
    }

    return EMPTY;
}
