#include <sstream>

#include "glud.h"

GLUD::GLUD(std::set<char> variables, std::set<char> terminals, std::map<char, std::vector<std::string>> productions, char start)
    : variables(variables), terminals(terminals), productions(productions), start(start)
{
}

bool GLUD::is_variable(char chr) const
{
    return this->variables.find(chr) != this->variables.end();
}

bool GLUD::is_terminal(char chr) const
{
    return this->terminals.find(chr) != this->terminals.end();
}

std::string GLUD::to_string() const
{
    std::stringstream ss;

    ss << "V = " << this->variables << '\n';
    ss << "T = " << this->terminals << '\n';
    ss << "P = " << this->productions << '\n';
    ss << "S = " << this->start << '\n';

    return ss.str();
}