#pragma once

#include "state.h"
#include "printable.h"

struct Transition: public Printable
{
    std::string to_string() const override;

    State origin;
    char symbol;
    State destination;
};