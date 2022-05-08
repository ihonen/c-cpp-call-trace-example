#ifdef __cplusplus
extern "C" {
#endif

#include "trace.h"

// This is a glibc extension header that provides a means of getting
// backtrace information.
#include <execinfo.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

#define UNUSED(arg) ((void)arg)

#define FUNC_NAME_MAX_LEN   ((size_t)64)
#define FUNC_OFFSET_MAX_LEN ((size_t)64)
#define FUNC_ADDR_MAX_LEN   ((size_t)64)

// -----------------------------------------------------------------------------

// Track the total number of function calls.
static uint_least64_t s_total_func_calls = 0;

// Track the length of the function call chain.
static int s_callstack_height = 0;

// -----------------------------------------------------------------------------

// NOTE: It is imperative that these functions be declared with
// __attribute__((no_instrument_function))! This instructs the compiler not to
// instrument these functions with calls to __cyg_profile_func_enter and
// __cyg_profile_func_exit. If you forget to declare a function called by
// either of those two functions with this attribute, the result will be an
// infinite recursion and your program will crash due to stack overflow.

static const char* s_get_func_name(
    const char* backtrace_str
) __attribute__((no_instrument_function));

static const char* s_get_func_offset(
    const char* backtrace_str
) __attribute__((no_instrument_function));

static const char* s_get_func_address(
    const char* backtrace_str
) __attribute__((no_instrument_function));

// -----------------------------------------------------------------------------

// The code is neither terribly efficient nor safe, but will suffice for the
// purposes of demonstration.

static const char* s_get_func_name(
    const char* backtrace_str
)
{
    static char func_name[FUNC_NAME_MAX_LEN];
    *func_name = '\0';

    const char* left = backtrace_str;
    while (*left != '(')
    {
        ++left;
    }
    ++left;

    const char* right = left;
    while (*right != '+')
    {
        ++right;
    }
    ++right;

    if (right > left + 1)
    {
        snprintf(func_name, right - left, "%s", left);
        return func_name;
    }

    return NULL;
}

static const char* s_get_func_offset(
    const char* backtrace_str
)
{
    static char func_offset[FUNC_OFFSET_MAX_LEN];
    *func_offset = '\0';

    const char* left = backtrace_str;
    while (*left != '+')
    {
        ++left;
    }
    ++left;

    if (left[0] == '0'
        && left[1] == 'x')
    {
        left += 2;
    }

    const char* right = left;
    while (*right != ')')
    {
        ++right;
    }
    ++right;

    if (right > left + 1)
    {
        snprintf(func_offset, right - left, "%s", left);
        return func_offset;
    }

    return NULL;
}

static const char* s_get_func_address(
    const char* backtrace_str
)
{
    static char func_address[FUNC_ADDR_MAX_LEN];
    *func_address = '\0';

    const char* left = backtrace_str;
    while (*left != '[')
    {
        ++left;
    }
    ++left;

    const char* right = left;
    while (*right != ']')
    {
        ++right;
    }
    ++right;

    if (right > left + 1)
    {
        snprintf(func_address, right - left, "%s", left);
        return func_address;
    }

    return NULL;
}

// -----------------------------------------------------------------------------

void __cyg_profile_func_enter(
    void* current_func,
    void* previous_func
)
{
    UNUSED(previous_func);

    // -----

    ++s_total_func_calls;
    ++s_callstack_height;
    assert(s_callstack_height > 0);

    // -----

    char** backtrace_strings = backtrace_symbols(&current_func, 1);
    char*  current_func_str  = backtrace_strings[0];

    // -----

    const char* func_name    = s_get_func_name(current_func_str);
    const char* func_offset  = s_get_func_offset(current_func_str);
    const char* func_address = s_get_func_address(current_func_str);

    printf(
        "<TRACE>%*c---> %s%s [%s] %i\n",
        s_callstack_height,
        ' ',
        func_name ? "" : "??? +0x",
        func_name ? func_name : func_offset,
        func_address,
        s_callstack_height - 1
    );

    // -----

    free(backtrace_strings);
}

void __cyg_profile_func_exit(
    void* current_func,
    void* previous_func
)
{
    UNUSED(previous_func);

    // -----

    char** backtrace_strings = backtrace_symbols(&current_func, 1);
    char*  current_func_str  = backtrace_strings[0];

    // -----

    const char* func_name    = s_get_func_name(current_func_str);
    const char* func_offset  = s_get_func_offset(current_func_str);
    const char* func_address = s_get_func_address(current_func_str);

    printf(
        "<TRACE>%*c<--- %s%s [%s] %i\n",
        s_callstack_height,
        ' ',
        func_name ? "" : "??? +0x",
        func_name ? func_name : func_offset,
        func_address,
        s_callstack_height - 1
    );

    // -----

    free(backtrace_strings);

    // -----

    --s_callstack_height;
    assert(s_callstack_height >= 0);
}
