#include "logger.h"

// cppcheck-suppress unusedFunction
__attribute__((constructor)) static void libcomserial_static_init()
{
#if HAVE_YAPLOG
    logger::setDestinationVariable("CSER_LOGDESTINATION");
    logger::setLevelVariable("CSER_LOGLEVEL");
#endif
    TLOG() << "Load comserial library";
}

// cppcheck-suppress unusedFunction
__attribute__((destructor)) static void libcomserial_static_deinit()
{
}
