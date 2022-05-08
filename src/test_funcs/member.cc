#include "member.hh"

// -----------------------------------------------------------------------------

Base::~Base()
{
}

void Base::virtual_foo()
{
}

// -----------------------------------------------------------------------------

Derived::~Derived()
{
}

void Derived::static_foo()
{
}

void Derived::nonvirtual_foo()
{
}

void Derived::virtual_foo()
{
}
