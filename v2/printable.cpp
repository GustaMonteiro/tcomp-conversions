#include "printable.h"

std::ostream &operator<<(std::ostream &stream, const Printable &printable)
{
    stream << printable.to_string();
    return stream;
}