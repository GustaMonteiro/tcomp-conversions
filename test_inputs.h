#pragma once

#include <sstream>
#include <vector>
#include <utility>
#include <string>
#include <iostream>

#include "glud.h"
#include "definitions.h"
#include "afnd.h"
#include "afd.h"

using Test_Input = std::vector<std::pair<std::string, bool>>;

struct Grammar_Test
{
    GLUD grammar;
    Test_Input inputs;
};

std::vector<Grammar_Test> all_tests{
    Grammar_Test{// Accept strings with at least one 'a' followed by only one 'b'
                 GLUD(
                     {'S', 'A'}, // Variables
                     {'a', 'b'}, // Terminals
                     {           // Productions
                      {'S', {"aA", EPSILON_STRING}},
                      {'A', {"aA", "b"}}},
                     'S' // Start symbol
                     ),
                 Test_Input{
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
                 }},

    Grammar_Test{// Accept strings with any number of 'ab' repetitions
                 GLUD(
                     {'S', 'A'}, // Variables
                     {'a', 'b'}, // Terminals
                     {           // Productions
                      {'S', {"aA", EPSILON_STRING}},
                      {'A', {"bS"}}},
                     'S' // Start symbol
                     ),
                 Test_Input{
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
                 }},

    Grammar_Test{// Accept strings with any number of 'a' followed by only one 'b'
                 GLUD(
                     {'S', 'A'},
                     {'a', 'b'},
                     {{'S', {"aS", "b"}}},
                     'S'),
                 Test_Input{
                     {"", false},
                     {"b", true},
                     {"a", false},
                     {"ab", true},
                     {"aab", true},
                     {"aaab", true},
                     {"ba", false},
                     {"bbb", false},
                     {"aaabb", false},
                 }},

    Grammar_Test{// Only accept the word 'ab'
                 GLUD(
                     {'S', 'A'},
                     {'a', 'b'},
                     {{'S', {"aA"}},
                      {'A', {"b"}}},
                     'S'),
                 Test_Input{
                     {"", false},
                     {"a", false},
                     {"b", false},
                     {"ab", true},
                     {"aa", false},
                     {"abb", false},
                     {"aab", false},
                 }},

    Grammar_Test{// Accept any string that finishes with 'ab'
                 GLUD(
                     {'S', 'A', 'B', 'F'},
                     {'a', 'b'},
                     {{'S', {"aS", "bS", "aA"}},
                      {'A', {"bF"}},
                      {'F', {EPSILON_STRING}}},
                     'S'),
                 Test_Input{
                     {"", false},
                     {"ab", true},
                     {"aab", true},
                     {"babab", true},
                     {"aaababbabbbababaababbababababababababbbabab", true},
                     {"aaba", false},
                     {"ba", false},
                     {"baba", false},
                     {"abab", true},
                     {"aba", false},
                 }},

    Grammar_Test{// Accept only the word 'a'
                 GLUD(
                     {'S', 'F'},
                     {'a'},
                     {{'S', {"aF"}},
                      {'F', {EPSILON_STRING}}},
                     'S'),
                 Test_Input{
                     {"", false},
                     {"a", true},
                     {"aa", false},
                     {"aaaaa", false},
                 }},

    Grammar_Test{// Accept only words with odd number of 'a'
                 GLUD(
                     {'S', 'A'},
                     {'a'},
                     {{'S', {"aA"}},
                      {'A', {"aS", EPSILON_STRING}}},
                     'S'),
                 Test_Input{
                     {"", false},
                     {"a", true},
                     {"aa", false},
                     {"aaaa", false},
                     {"aaa", true},
                     {"aaaaa", true},
                     {"aaaaaa", false},
                 }}

};

std::string reverse_string(const std::string &str)
{
    std::stringstream ss;

    for (auto rit = str.rbegin(); rit != str.rend(); rit++)
        ss << *rit;

    return ss.str();
}

bool run_all_grammar_tests()
{
    bool something_failed = false;

    for (auto &[grammar, inputs] : all_tests)
    {
        AFND afnd(grammar);
        AFD afd(afnd);
        AFD reversed_afd = afd.reverse();
        AFD complement_afd = afd.complement();

        bool something_on_current_test_failed = false;

        for (auto &[input, expected] : inputs)
        {
            bool result = afd.accept_string(input);
            if (expected != result)
            {
                if (!something_on_current_test_failed)
                {
                    std::cout << "> Something failed on:\n\ngrammar:\n"
                              << grammar << "\nafd:\n"
                              << afd << "\nreversed_afd:\n"
                              << reversed_afd << "\ncomplement_afd:\n"
                              << complement_afd << "\n";
                    something_on_current_test_failed = true;
                }

                std::cout << "[Original AFD] - Input: " << input << ", expected: " << expected << ", result: " << result << '\n';
                something_failed = true;
            }
        }

        for (auto [input, expected] : inputs)
        {
            input = reverse_string(input);
            bool result = reversed_afd.accept_string(input);

            if (expected != result)
            {
                if (!something_on_current_test_failed)
                {
                    std::cout << "> Something failed on:\n\ngrammar:\n"
                              << grammar << "\nafd:\n"
                              << afd << "\nreversed_afd:\n"
                              << reversed_afd << "\ncomplement_afd:\n"
                              << complement_afd << "\n";
                    something_on_current_test_failed = true;
                }

                std::cout << "[Reversed AFD] - Input: " << input << ", expected: " << expected << ", result: " << result << '\n';
                something_failed = true;
            }
        }

        for (auto [input, expected] : inputs)
        {
            expected = !expected;
            bool result = complement_afd.accept_string(input);

            if (expected != result)
            {
                if (!something_on_current_test_failed)
                {
                    std::cout << "> Something failed on:\n\ngrammar:\n"
                              << grammar << "\nafd:\n"
                              << afd << "\nreversed_afd:\n"
                              << reversed_afd << "\ncomplement_afd:\n"
                              << complement_afd << "\n";
                    something_on_current_test_failed = true;
                }

                std::cout << "[Complement AFD] - Input: " << input << ", expected: " << expected << ", result: " << result << '\n';
                something_failed = true;
            }
        }
    }

    return something_failed;
}