#include "comserial/cppcomserial.h"
#include "logger.h"

#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

using namespace com;

serial::serial(const std::string &device)
    : m_fd(-1)
{
    open_device(device.c_str());
}

serial::~serial()
{
    close_device();
}

void serial::open_device(const char *device)
{
    m_fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY | O_SYNC);
    if (m_fd < 0) {
        m_fd = -1;
        throw com::exception::device_not_found();
    }
}

void serial::close_device()
{
    if (m_fd != -1) {
        close(m_fd);
        m_fd = -1;
    }
}
