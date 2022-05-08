#include "throw.hh"

#include <stdexcept>

// -----------------------------------------------------------------------------

void mynamespace::throwing_foo()
{
    throw std::exception();
}
