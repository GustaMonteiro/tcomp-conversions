#include <stdexcept>

#include "file_reader.h"

GLUD read_grammar_from_file(std::filesystem::path file_path)
{
    std::ifstream file(file_path);
    if(!file.is_open())
        throw std::runtime_error("Couldn't open file");

    GLUD grammar;

    int number_of_variables = -1, number_of_terminals = -1, number_of_productions = -1;

    file >> number_of_variables;

    if (number_of_variables < 0)
        throw std::runtime_error("Cannot have negative number of variables");

    for (int i = 0; i < number_of_variables; i++)
    {
        char variable = '.';
        file >> variable;
        grammar.variables.insert(variable);
    }

    file >> number_of_terminals;

    if (number_of_terminals < 0)
        throw std::runtime_error("Cannot have negative number of terminals");

    for (int i = 0; i < number_of_terminals; i++)
    {
        char terminal = '.';
        file >> terminal;
        grammar.terminals.insert(terminal);
    }

    file >> number_of_productions;

    if (number_of_productions < 0)
        throw std::runtime_error("Cannot have negative number of productions");

    for (int i = 0; i < number_of_productions; i++)
    {
        char variable = '.';
        file >> variable;

        std::string arrow;
        file >> arrow;

        if (arrow != "->")
            throw std::runtime_error("Production malformed");

        std::string production;
        file >> production;

        grammar.productions[variable].push_back(production);
    }

    file >> grammar.start;

    file.close();

    return grammar;
}