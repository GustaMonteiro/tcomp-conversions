#include "printable.h"
#include "state.h"
#include "transition.h"

std::ostream &operator<<(std::ostream &stream, const Printable &printable)
{
    stream << printable.to_string();
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const std::set<State>& states)
{
    stream << '{';

    bool need_comma = false;

    for (auto &state : states)
    {
        if (need_comma)
            stream << ", ";

        stream << state;

        need_comma = true;
    }

    stream << '}';

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const std::set<Transition>& transitions)
{
    stream << "{\n";

    for (auto &transition : transitions)
        stream << '\t' << transition << '\n';

    stream << '}';

    return stream;
}
// 

std::ostream &operator<<(std::ostream &stream, const std::set<char> &set)
{
    stream << '{';

    bool need_comma = false;

    for (auto &value : set)
    {
        if (need_comma)
            stream << ", ";

        stream << value;

        need_comma = true;
    }

    stream << '}';

    return stream;
}

std::ostream &operator<<(std::ostream &stream, const std::set<std::string> &set)
{
    stream << '{';

    bool need_comma = false;

    for (auto &value : set)
    {
        if (need_comma)
            stream << ", ";

        stream << value;

        need_comma = true;
    }

    stream << '}';

    return stream;
}

std::ostream &operator<<(std::ostream &stream, const std::map<char, std::vector<std::string>> &productions)
{
    stream << "{\n";

    for (auto &[alpha, betas] : productions)
    {
        stream << '\t' << alpha << " -> ";

        bool need_pipe = false;

        for (auto &beta : betas)
        {
            if (need_pipe)
                stream << " | ";

            stream << beta;

            need_pipe = true;
        }

        stream << '\n';
    }

    stream << '}';

    return stream;
}
