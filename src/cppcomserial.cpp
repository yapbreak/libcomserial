#include "comserial/cppcomserial.h"
#include "logger.h"

#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

using namespace com;

serial::serial(const std::string &device)
{
    open_device(device.c_str());
}

void serial::open_device(const char *device)
{
    m_fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY | O_SYNC);
    if (m_fd < 0) {
        m_fd = -1;
        throw com::exception::device_not_found();
    }
}
