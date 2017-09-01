#include "comserial/cppcomserial.h"
#include "logger.h"

using namespace com;

serial::serial(const std::string &device)
{
    (void) device;
    ILOG() << "Build new serial device bound by " << device;
    throw exception::device_not_found();
}
