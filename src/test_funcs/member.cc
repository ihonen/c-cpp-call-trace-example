#include "member.hh"

// -----------------------------------------------------------------------------

mynamespace::Base::~Base()
{
}

void mynamespace::Base::virtual_foo()
{
}

// -----------------------------------------------------------------------------

mynamespace::Derived::~Derived()
{
}

void mynamespace::Derived::static_foo()
{
}

void mynamespace::Derived::nonvirtual_foo()
{
}

void mynamespace::Derived::virtual_foo()
{
}
