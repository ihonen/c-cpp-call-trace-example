#pragma once

// -----------------------------------------------------------------------------

static void static_foo() __attribute__((noinline));
static void static_bar() __attribute__((noinline));

// -----------------------------------------------------------------------------

void static_foo()
{
    static_bar();
}

void static_bar()
{
}
