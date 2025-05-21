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
    return std::string();
}