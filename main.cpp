#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include <sstream>

#include "glud.h"
#include "afd.h"
#include "afnd.h"
#include "definitions.h"
#include "test_inputs.h"

int main(int argc, char **argv)
{
    if (argc > 1 && std::string(argv[1]) == "-t")
    {
        if (run_all_grammar_tests())
            return -1;

        std::cout << "All tests passed!\n\n";
        return 0;
    }

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

    std::vector<std::pair<std::string, bool>> inputs{
        {"", true},
        {"a", false},
        {"b", false},
        {"ab", true},
        {"ba", false},
        {"aab", false},
        {"aabb", false},
        {"aaaaaaaab", false},
        {"aaaaaaaaaabb", false},
        {"aaaaaabaaab", false},
        {"abab", true},
        {"ababababab", true},
        {"abababaabab", false},
        {"abababbabab", false},
        {"ababababa", false},
        {"bababab", false},
    };
#endif

    std::cout << "=> Original Grammar:\n";
    std::cout << grammar << '\n';

    AFND afnd(grammar);
    std::cout << "=> Original AFND:\n";
    std::cout << afnd << '\n';

    AFD afd(afnd);
    std::cout << "=> Original AFD:\n";
    std::cout << afd << '\n';

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
    std::cout << '\n';

    AFD complement_afd = afd.complement();

    std::cout << "Complement AFD:\n";
    std::cout << complement_afd << '\n';

    std::cout << "-> Testing inputs for Complement AFD:\n";
    for (auto [input, expected] : inputs)
    {
        expected = !expected;
        std::cout << "Input: " << input << ", expected: " << expected << ", result: " << complement_afd.accept_string(input) << '\n';
    }
}
