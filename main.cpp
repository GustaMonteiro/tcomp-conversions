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

void write_to_file(Printable &object, std::filesystem::path file_name);
void execute_conversions_and_tests(GLUD grammar, Test_Input inputs = {});
void generate_expected_outputs(GLUD grammar, std::string input);

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
    else if(argc == 5 && std::string(argv[1]) == "-f" && std::string(argv[3]) == "-w")
    {
        std::filesystem::path file_path(argv[2]);

        if (!std::filesystem::exists(file_path))
            return std::cout << "The file " << file_path.string() << " doesn't exist!\n", -1;

        std::string input(argv[4]);

        GLUD grammar = read_grammar_from_file(file_path);

        generate_expected_outputs(grammar, input);
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

void write_to_file(Printable &object, std::filesystem::path file_name)
{
    std::ofstream file(file_name);

    if (!file.is_open())
        throw std::runtime_error("Couldn't open file for writing output");

    file << object << '\n';

    file.close();
}

void execute_conversions_and_tests(GLUD grammar, Test_Input inputs)
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

void generate_expected_outputs(GLUD grammar, std::string input)
{
    AFND afnd(grammar);
    AFD afd(afnd);
    AFD reverse = afd.reverse();
    AFD complement = afd.complement();

    write_to_file(afnd, "AFN.txt");
    write_to_file(afd, "AFD.txt");
    write_to_file(reverse, "REV.txt");
    write_to_file(complement, "COMP.txt");

    bool result = afd.accept_string(input);

    std::cout << "Cadeia: " << input << '\n';
    std::cout << "Resultado: " << (result ? "Aceita" : "Rejeita") << '\n';
    std::cout << "Arquivos gerados: AFN.txt, AFD.txt, REV.txt, COMP.txt\n";
}