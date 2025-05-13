#include <iostream>

#include "structs.h"

int main()
{
    GLUD grammar(
        {'S', 'A'}, // Variables
        {'a', 'b'}, // Terminals
        {           // Productions
         {'S', {"aA"}},
         {'A', {"aA", "b"}}},
        'S' // Start symbol
    );

    std::cout << grammar << '\n';

    AFND afnd(grammar);

    std::cout << afnd << '\n';

    AFD afd(afnd);

    std::cout << afd << '\n';
}
