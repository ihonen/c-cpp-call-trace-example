extern "C" {
#include "extern.h"
#include "inline.h"
#include "static.h"
}

#include "member.hh"
#include "template.hh"
#include "throw.hh"

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
        throwing_foo();
    }
    catch (...)
    {
    }

    // -----

    printf("\n");
    printf("*** Template functions ***\n");
    printf("\n");
    template_foo<int>();

    // -----

    printf("\n");
    printf("*** Constructors ***\n");
    printf("\n");
    Derived* derived = new Derived();

    // -----

    printf("\n");
    printf("*** Static member functions ***\n");
    printf("\n");
    Derived::static_foo();

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