#include <iostream>

#include "structs.h"

int main()
{
    GLUD grammar(
        {'S', 'A'}, // Variables
        {'a', 'b'}, // Terminals
        {           // Productions
            {'S', {"aA"}},
            {'A', {"aA", "b"}}
        },
        'S'         // Start symbol
    );

    std::cout << grammar << '\n';
}
