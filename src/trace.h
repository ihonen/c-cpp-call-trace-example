#pragma once

// -----------------------------------------------------------------------------

void __cyg_profile_func_enter(
    void* current_func,
    void* previous_func
) __attribute__((no_instrument_function));

void __cyg_profile_func_exit(
    void* current_func,
    void* previous_func
) __attribute__((no_instrument_function));
