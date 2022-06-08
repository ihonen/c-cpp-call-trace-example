// NOTE: This file can also be compiled as C, but that will disable C++ symbol
// demangling (it's not trivial to demangle them in code that is compiled as C).

#include <sys/stat.h>
#include <sys/types.h>

#ifdef __cplusplus
# include <cxxabi.h>
#endif
#include <execinfo.h>
#include <unistd.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// -----------------------------------------------------------------------------

#define UNUSED(arg) ((void)arg)

// -----------------------------------------------------------------------------

// NOTE: It is imperative that these functions be declared with
// __attribute__((no_instrument_function))! This instructs the compiler not to
// instrument these functions with calls to __cyg_profile_func_enter and
// __cyg_profile_func_exit. If you forget to declare a function called by
// either of those two functions with this attribute, the result will be an
// infinite recursion and the process will crash due to stack overflow.

#ifdef __cplusplus
extern "C" {
#endif

static char* demangle_func_identifier(
    const char* func_identifier
) __attribute__((no_instrument_function));

static const char* get_func_identifier(
    char* backtrace_str
) __attribute__((no_instrument_function));

static void init_trace(
) __attribute__((no_instrument_function));

void __cyg_profile_func_enter(
    void* current_func,
    void* previous_func
) __attribute__((no_instrument_function));

void __cyg_profile_func_exit(
    void* current_func,
    void* previous_func
) __attribute__((no_instrument_function));

// -----

static const size_t DemangleBufferSizeDefault = 4096;

// -----

// Preallocate a buffer for the demangled name for higher performance.
char*  g_demangle_buffer      = NULL;
size_t g_demangle_buffer_size = 0;

static uint_least64_t g_total_func_calls = 0;
static int_fast32_t   g_callchain_len = 0;

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

char* demangle_func_identifier(const char* func_identifier)
{
#ifdef __cplusplus
    return abi::__cxa_demangle(
        func_identifier,
        g_demangle_buffer,
        &g_demangle_buffer_size,
        NULL
    );
#else
    UNUSED(func_identifier);
    return NULL;
#endif
}

// NOTE: This function may modify its argument!
const char* get_func_identifier(char* backtrace_str)
{
    char* func_name_begin = backtrace_str;
    while (*func_name_begin != '(')
    {
        ++func_name_begin;
    }
    ++func_name_begin;

    char* func_name_end = func_name_begin;
    while (*func_name_end != '+')
    {
        ++func_name_end;
    }

    if (func_name_end != func_name_begin)
    {
        // We know the function name. Try to demangle it.
        *func_name_end = '\0';
        char* demangled_name = demangle_func_identifier(func_name_begin);
        return demangled_name ? demangled_name : func_name_begin;
    }
    else
    {
        // The function name is unknown, use the offset to
        // identify the function instead.
        char* offset_begin = func_name_end;
        char* offset_end = offset_begin;
        while (*offset_end != ')')
        {
            ++offset_end;
        }
        *offset_end = '\0';
        return offset_begin;
    }
}

// -----------------------------------------------------------------------------

void init_trace()
{
    g_demangle_buffer_size = DemangleBufferSizeDefault;
    g_demangle_buffer      = (char*)malloc(g_demangle_buffer_size);
}

// -----------------------------------------------------------------------------

void __cyg_profile_func_enter(
    void* current_func,
    void* previous_func
)
{
    UNUSED(previous_func);

    // -----

    ++g_total_func_calls;
    ++g_callchain_len;

    // -----

    static bool initialized = false;
    if (!initialized)
    {
        init_trace();
        initialized = true;
    }

    // -----

    char** backtrace_strings = backtrace_symbols(&current_func, 1);
    char*  current_func_str  = backtrace_strings[0];

    fprintf(
        stdout,
        "%*c---> %s\n",
        (int)g_callchain_len,
        ' ',
        get_func_identifier(current_func_str)
    );

    free(backtrace_strings);
}

void __cyg_profile_func_exit(
    void* current_func,
    void* previous_func
)
{
    UNUSED(current_func);
    UNUSED(previous_func);

    // -----

    --g_callchain_len;

    // -----

    char** backtrace_strings = backtrace_symbols(&current_func, 1);
    char*  current_func_str  = backtrace_strings[0];

    fprintf(
        stdout,
        "%*c<--- %s\n",
        (int)g_callchain_len,
        ' ',
        get_func_identifier(current_func_str)
    );

    free(backtrace_strings);
}
