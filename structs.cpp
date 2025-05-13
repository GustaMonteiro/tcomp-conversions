#include <sstream>

#include "structs.h"
#include "utils.h"

std::string State::to_string() const
{
    std::stringstream ss;

    if(this->components.size() == 1)
        ss << *components.begin();
    else
        ss << set_as_string(this->components);

    return ss.str();
}

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
    : alphabet(grammar.terminals)
{
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

AFD::AFD(AFND automata)
    : alphabet(automata.alphabet)
{
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
