#include <sstream>

#include "afd.h"
#include "utils.h"

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