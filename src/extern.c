#ifdef __cplusplus
extern "C" {
# include "extern.h"
}
#else
# include "extern.h"
#endif

// -----------------------------------------------------------------------------

void extern_foo()
{
    extern_bar();
}

void extern_bar()
{
}
