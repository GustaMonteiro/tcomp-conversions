#pragma once

#include "state.h"
#include "printable.h"

struct Transition: public Printable
{
    Transition(State origin, char symbol, State destination);

    std::string to_string() const override;

    State origin;
    char symbol;
    State destination;
};

bool operator<(const Transition& left, const Transition& right);