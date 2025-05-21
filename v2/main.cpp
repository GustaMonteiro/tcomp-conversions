#include <iostream>
#include <set>
#include <vector>
#include <utility>

#include "glud.h"
#include "afd.h"
#include "afnd.h"
#include "definitions.h"

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

    std::cout << grammar << '\n';

    AFND afnd(grammar);
    std::cout << afnd << '\n';

    AFD afd(afnd);
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

    for (auto &[input, expected] : inputs)
        std::cout << "Input: " << input << ", expected: " << expected << ", result: " << afd.accept_string(input) << '\n';
}
