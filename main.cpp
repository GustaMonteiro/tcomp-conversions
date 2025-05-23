#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include <sstream>
#include <filesystem>

#include "glud.h"
#include "afd.h"
#include "file_reader.h"
#include "afnd.h"
#include "definitions.h"
#include "test_inputs.h"

void execute_conversions_and_tests(GLUD grammar, Test_Input inputs = {})
{
    std::cout << "=> Original Grammar:\n";
    std::cout << grammar << '\n';

    AFND afnd(grammar);
    std::cout << "=> Original AFND:\n";
    std::cout << afnd << '\n';

    AFD afd(afnd);
    std::cout << "=> Original AFD:\n";
    std::cout << afd << '\n';

    if (!inputs.empty())
    {
        std::cout << "-> Testing inputs for AFD:\n";
        for (auto &[input, expected] : inputs)
            std::cout << "Input: " << input << ", expected: " << expected << ", result: " << afd.accept_string(input) << '\n';
        std::cout << '\n';
    }

    AFD reversed_afd = afd.reverse();

    std::cout << "=> Reversed AFD:\n";
    std::cout << reversed_afd << '\n';

    if (!inputs.empty())
    {
        std::cout << "-> Testing reversed inputs for Reversed AFD:\n";
        for (auto [input, expected] : inputs)
        {
            input = reverse_string(input);
            std::cout << "Input: " << input << ", expected: " << expected << ", result: " << reversed_afd.accept_string(input) << '\n';
        }
        std::cout << '\n';
    }

    AFD complement_afd = afd.complement();

    std::cout << "=> Complement AFD:\n";
    std::cout << complement_afd << '\n';

    if (!inputs.empty())
    {
        std::cout << "-> Testing inputs for Complement AFD:\n";
        for (auto [input, expected] : inputs)
        {
            expected = !expected;
            std::cout << "Input: " << input << ", expected: " << expected << ", result: " << complement_afd.accept_string(input) << '\n';
        }
    }
}

int main(int argc, char **argv)
{
    if (argc == 2 && std::string(argv[1]) == "-t")
    {
        if (run_all_grammar_tests())
            return -1;

        std::cout << "All tests passed!\n\n";
        return 0;
    }
    else if (argc == 3 && std::string(argv[1]) == "-f")
    {
        std::filesystem::path file_path(argv[2]);

        if (!std::filesystem::exists(file_path))
            return std::cout << "The file " << file_path.string() << " doesn't exist!\n", -1;

        GLUD grammar = read_grammar_from_file(file_path);

        execute_conversions_and_tests(grammar);
    }
    else
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

        execute_conversions_and_tests(grammar, inputs);
    }
}
