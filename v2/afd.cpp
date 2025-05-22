#include <sstream>

#include "afd.h"

AFD::AFD(AFND afnd)
{
    *this = afnd.convert_to_deterministic();
}

bool AFD::accept_string(std::string str) const
{
    return false;
}

bool AFD::contain_state(State state) const
{
    return this->states.find(state) != this->states.end();
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
