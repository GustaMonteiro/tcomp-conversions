#include <sstream>

#include "transition.h"

Transition::Transition(State origin, char symbol, State destination)
    : origin(origin), symbol(symbol), destination(destination)
{
}

std::string Transition::to_string() const
{
    std::stringstream ss;
    ss << '(' << origin << ", " << symbol << ") -> " << destination;
    return ss.str();
}

bool operator<(const Transition &left, const Transition &right)
{
    if (left.origin < right.origin)
        return true;
    if (right.origin < left.origin)
        return false;

    if (left.symbol < right.symbol)
        return true;
    if (right.symbol < left.symbol)
        return false;

    return left.destination < right.destination;
}
