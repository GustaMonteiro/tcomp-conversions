#include "utils.h"

#include <sstream>

std::string set_as_string(const std::set<char>& set, std::string name)
{
    std::stringstream ss;

    ss << name << " = {";

    bool need_comma = false;

    for(auto& value : set)
    {
        if(need_comma)
            ss << ", ";

        ss << value;

        need_comma = true;
    }

    ss << '}';

    return ss.str();
}

std::string productions_as_string(const Productions& productions, std::string name)
{
    std::stringstream ss;

    ss << name << " = {\n";

    for(auto& [alpha, betas]: productions)
    {
        ss << '\t' << alpha << " -> ";
        
        bool need_pipe = false;

        for(auto& beta: betas)
        {
            if(need_pipe)
                ss << " | ";

            ss << beta;

            need_pipe = true;
        }

        ss << '\n';
    }

    ss << '}';

    return ss.str();
}

std::string transitions_as_string(const Transitions &transitions, std::string name)
{
    std::stringstream ss;

    ss << name << " = {\n";

    for(auto& [origin, paths]: transitions)
    {
        for(auto& [symbol, destination]: paths)
            ss << "\t(" << origin << ", " << symbol << ") -> " << destination << '\n';
    }

    ss << '}';

    return ss.str();
}

std::ostream& operator<<(std::ostream &stream, Stringfiable& object)
{
    stream << object.to_string();
    return stream;
}
