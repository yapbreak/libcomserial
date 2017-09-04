#include "comserial/cppcomserial.h"
#include "logger.h"

#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

using namespace com;

serial::serial(const std::string &device, unsigned int speed)
    : m_fd(-1)
    , m_speed(speed)
{
    check_and_set_speed(speed);

    open_device(device.c_str());
}

serial::~serial()
{
    close_device();
}

unsigned int serial::get_speed() const
{
    return m_speed;
}

unsigned int serial::set_speed(unsigned int speed)
{
    check_and_set_speed(speed);

    unsigned int old_speed = m_speed;
    m_speed = speed;
    return old_speed;
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

void serial::check_and_set_speed(unsigned int new_speed)
{
#define VALID(value) case value: \
    m_termios_speed = B ## value; \
    break;
    switch (new_speed) {
        VALID(50)
        VALID(75)
        VALID(110)
        VALID(134)
        VALID(150)
        VALID(200)
        VALID(300)
        VALID(600)
        VALID(1200)
        VALID(1800)
        VALID(2400)
        VALID(4800)
        VALID(9600)
        VALID(19200)
        VALID(38400)
        VALID(57600)
        VALID(115200)
        VALID(230400)
        default:
            throw com::exception::invalid_speed(new_speed);
    }
}
