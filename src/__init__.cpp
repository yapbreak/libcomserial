#include "logger.h"

// cppcheck-suppress unusedFunction
__attribute__((constructor)) static void libcomserial_static_init()
{
    TLOG() << "Load comserial library";
}

// cppcheck-suppress unusedFunction
__attribute__((destructor)) static void libcomserial_static_deinit()
{
    TLOG() << "Unload comserial library";
}
