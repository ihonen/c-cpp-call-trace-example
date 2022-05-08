#pragma once

// -----------------------------------------------------------------------------

static inline void inline_foo() __attribute__((always_inline));
static inline void inline_bar() __attribute__((always_inline));

// -----------------------------------------------------------------------------

void inline_foo()
{
    inline_bar();
}

void inline_bar()
{
}
