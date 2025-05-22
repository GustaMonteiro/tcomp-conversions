#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include <sstream>

#include "glud.h"
#include "afd.h"
#include "afnd.h"
#include "definitions.h"

static std::string reverse_string(const std::string &str)
{
    std::stringstream ss;

    for (auto rit = str.rbegin(); rit != str.rend(); rit++)
        ss << *rit;

    return ss.str();
}

int main()
{
#if 1
    // MY GRAMMAR:

    GLUD grammar(
        {'S', 'A'}, // Variables
        {'a', 'b'}, // Terminals
        {           // Productions
         {'S', {"aA", EPSILON_STRING}},
         {'A', {"aA", "b"}}},
        'S' // Start symbol
    );

#else
    // PROFESSOR'S GRAMMAR

    GLUD grammar(
        {'S', 'A'}, // Variables
        {'a', 'b'}, // Terminals
        {           // Productions
         {'S', {"aA", EPSILON_STRING}},
         {'A', {"bS"}}},
        'S' // Start symbol
    );
#endif

    std::cout << "=> Original Grammar:\n";
    std::cout << grammar << '\n';

    AFND afnd(grammar);
    std::cout << "=> Original AFND:\n";
    std::cout << afnd << '\n';

    AFD afd(afnd);
    std::cout << "=> Original AFD:\n";
    std::cout << afd << '\n';

    std::vector<std::pair<std::string, bool>> inputs{
        {"", true},
        {"a", false},
        {"b", false},
        {"ab", true},
        {"ba", false},
        {"aab", true},
        {"aabb", false},
        {"aaaaaaaab", true},
        {"aaaaaaaaaabb", false},
        {"aaaaaabaaab", false},
    };

    std::cout << "-> Testing inputs for AFD:\n";
    for (auto &[input, expected] : inputs)
        std::cout << "Input: " << input << ", expected: " << expected << ", result: " << afd.accept_string(input) << '\n';
    std::cout << '\n';

    AFD reversed_afd = afd.reverse();

    std::cout << "Reversed AFD:\n";
    std::cout << reversed_afd << '\n';

    std::cout << "-> Testing reversed inputs for Reversed AFD:\n";
    for (auto [input, expected] : inputs)
    {
        input = reverse_string(input);
        std::cout << "Input: " << input << ", expected: " << expected << ", result: " << reversed_afd.accept_string(input) << '\n';
    }
}
