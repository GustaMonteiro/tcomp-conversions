#include "utils.h"

#include <sstream>

std::string vector_as_string(const std::vector<char> &vec, std::string name)
{
    std::stringstream ss;

    if (!name.empty())
        ss << name << " = ";

    ss << '{';

    bool need_comma = false;

    for (auto &value : vec)
    {
        if (need_comma)
            ss << ", ";

        ss << value;

        need_comma = true;
    }

    ss << '}';

    return ss.str();
}

std::string vector_as_string(const std::vector<State> &vec, std::string name)
{
    std::stringstream ss;

    if (!name.empty())
        ss << name << " = ";

    ss << '{';

    bool need_comma = false;

    for (const auto &value : vec)
    {
        if (need_comma)
            ss << ", ";

        ss << value;

        need_comma = true;
    }

    ss << '}';

    return ss.str();
}

std::string vector_as_string(const std::vector<State *> &vec, std::string name)
{
    std::stringstream ss;

    if (!name.empty())
        ss << name << " = ";

    ss << '{';

    bool need_comma = false;

    for (const auto &value : vec)
    {
        if (need_comma)
            ss << ", ";

        ss << *value;

        need_comma = true;
    }

    ss << '}';

    return ss.str();
}

std::string set_as_string(const std::set<char> &set, std::string name)
{
    std::stringstream ss;

    if (!name.empty())
        ss << name << " = ";

    ss << '{';

    bool need_comma = false;

    for (auto &value : set)
    {
        if (need_comma)
            ss << ", ";

        ss << value;

        need_comma = true;
    }

    ss << '}';

    return ss.str();
}

std::string productions_as_string(const Productions &productions, std::string name)
{
    std::stringstream ss;

    ss << name << " = {\n";

    for (auto &[alpha, betas] : productions)
    {
        ss << '\t' << alpha << " -> ";

        bool need_pipe = false;

        for (auto &beta : betas)
        {
            if (need_pipe)
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

    for (auto &[origin, symbol, destination] : transitions)
        ss << "\t(" << origin << ", " << symbol << ") -> " << destination << '\n';

    ss << '}';

    return ss.str();
}

std::ostream &operator<<(std::ostream &stream, const Stringfiable &object)
{
    stream << object.to_string();
    return stream;
}

std::vector<State> generate_subsets(std::vector<State> states)
{
    int n = states.size();
    std::vector<State> subsets;

    for (int mask = 1; mask < (1 << n); mask++)
    {
        State state;

        for (int i = 0; i < n; i++)
        {
            if (mask & (1 << i))
            {
                state = state + states[i];
            }
        }

        subsets.push_back(state);
    }

    return subsets;
}
