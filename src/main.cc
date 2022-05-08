extern "C" {
#include "test_funcs/extern.h"
#include "test_funcs/inline.h"
#include "test_funcs/static.h"
}

#include "test_funcs/member.hh"
#include "test_funcs/template.hh"
#include "test_funcs/throw.hh"

#include <cstdio>

// -----------------------------------------------------------------------------

int main()
{
    // -----

    printf("\n");
    printf("---------------------------------------------------------------\n");
    printf("C LINKAGE\n");
    printf("---------------------------------------------------------------\n");

    // -----

    printf("\n");
    printf("*** Static functions ***\n");
    printf("\n");
    static_foo();

    // -----

    printf("\n");
    printf("*** Inline functions ***\n");
    printf("\n");
    inline_foo();

    // -----


    printf("\n");
    printf("*** Extern functions ***\n");
    printf("\n");
    extern_foo();

    // -----

    printf("\n");
    printf("---------------------------------------------------------------\n");
    printf("C++ LINKAGE\n");
    printf("---------------------------------------------------------------\n");

    // -----

    printf("\n");
    printf("*** Throwing functions ***\n");
    printf("\n");
    try
    {
        mynamespace::throwing_foo();
    }
    catch (...)
    {
    }

    // -----

    printf("\n");
    printf("*** Template functions ***\n");
    printf("\n");
    mynamespace::template_foo<int>();

    // -----

    printf("\n");
    printf("*** Constructors ***\n");
    printf("\n");
    auto* derived = new mynamespace::Derived();

    // -----

    printf("\n");
    printf("*** Static member functions ***\n");
    printf("\n");
    mynamespace::Derived::static_foo();

    // -----

    printf("\n");
    printf("*** Member functions ***\n");
    printf("\n");
    derived->nonvirtual_foo();

    // -----

    printf("\n");
    printf("*** Virtual member functions ***\n");
    printf("\n");
    derived->virtual_foo();

    // -----

    printf("\n");
    printf("*** Destructors ***\n");
    printf("\n");
    delete derived;

    // -----

    printf("\n");
    printf("---------------------------------------------------------------\n");
    printf("\n");

    // -----

    return 0;
}
