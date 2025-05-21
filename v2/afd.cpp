#include <sstream>

#include "afd.h"

AFD::AFD(AFND afnd)
{
}

bool AFD::accept_string(std::string str) const
{
    return false;
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
