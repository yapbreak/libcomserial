#include "comserial/cppcomserial.h"

using namespace com;

serial::serial(const std::string &device)
{
    (void) device;
    throw exception::device_not_found();
}
