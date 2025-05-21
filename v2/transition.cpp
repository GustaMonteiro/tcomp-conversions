#include <sstream>

#include "transition.h"

std::string Transition::to_string() const
{
    std::stringstream ss;
    ss << '(' << origin << ", " << symbol << ") -> " << destination;
    return ss.str();
}