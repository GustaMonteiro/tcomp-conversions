#include <sstream>

#include "afnd.h"

AFND::AFND(GLUD grammar)
{
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