#include <sstream>

#include "structs.h"
#include "utils.h"

GLUD::GLUD(std::set<char> variables, std::set<char> terminals, std::map<char, std::vector<std::string>> productions, char start)
    : variables(variables), terminals(terminals), productions(productions), start(start)
{
}

std::string GLUD::to_string()
{
    std::stringstream ss;

    ss << set_as_string(this->variables, "V") << '\n';
    ss << set_as_string(this->terminals, "T") << '\n';
    ss << productions_as_string(this->productions, "P") << '\n';
    ss << "S = " << this->start << '\n';

    return ss.str();
}

AFND::AFND(GLUD grammar)
{
}

std::string AFND::to_string()
{
    return "AFND";
}

AFD::AFD(AFND automata)
{
}

std::string AFD::to_string()
{
    return "AFD";
}

bool AFD::recognize_string(std::string input)
{
    return false;
}

AFD AFD::reverse()
{
    return AFD(AFND(GLUD({}, {}, {}, ' ')));
}

AFD AFD::complement()
{
    return AFD(AFND(GLUD({}, {}, {}, ' ')));
}
