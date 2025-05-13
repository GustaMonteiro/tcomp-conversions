#include <sstream>

#include "glud.h"
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