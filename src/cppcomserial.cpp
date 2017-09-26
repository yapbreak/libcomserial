#include "comserial/cppcomserial.h"
#include "logger.h"

#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

using namespace com;

serial::serial(const std::string &device, unsigned int speed,
                                          unsigned int data_size,
                                          unsigned int stop_size,
                                          char parity)
    : m_fd(-1)
    , m_speed(speed)
    , m_datasize(data_size)
    , m_stopsize(stop_size)
    , m_parity(parity)
    , m_options()
{
    // Set default termios configuration
    cfmakeraw(&m_options);
    m_options.c_cflag &= ~CRTSCTS;
    m_options.c_cflag |= (CLOCAL | CREAD);
    m_options.c_lflag &= ~(ICANON | ECHO | ECHONL | ISIG | IEXTEN);
    m_options.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK
                         | ISTRIP | IXON);
    m_options.c_oflag = 0;
    m_options.c_cc[VMIN] = 1;
    m_options.c_cc[VTIME] = 0;

    check_and_set_speed(speed);
    check_and_set_data_size(data_size);
    check_and_set_stop_size(stop_size);
    check_and_set_parity(parity);

    open_device(device.c_str());

    commit_termios_configuration();
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

    commit_termios_configuration();

    return old_speed;
}

unsigned int serial::get_data_size() const
{
    return m_datasize;
}

unsigned int serial::set_data_size(unsigned int data_size)
{
    check_and_set_data_size(data_size);

    unsigned int old_datasize = m_datasize;
    m_datasize = data_size;

    commit_termios_configuration();

    return old_datasize;
}

unsigned int serial::get_stop_size() const
{
    return m_stopsize;
}

unsigned int serial::set_stop_size(unsigned int stop_size)
{
    check_and_set_stop_size(stop_size);

    unsigned int old_stopsize = m_stopsize;
    m_stopsize = stop_size;

    commit_termios_configuration();

    return old_stopsize;
}

char serial::get_parity() const
{
    return m_parity;
}

char serial::set_parity(char parity)
{
    check_and_set_parity(parity);

    char old_parity = m_parity;
    m_parity = (parity < 'a') ? (parity + ('a' - 'A')) : parity;

    commit_termios_configuration();

    return old_parity;
}

void serial::open_device(const char *device)
{
    m_fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY | O_SYNC);
    if (m_fd < 0) {
        m_fd = -1;
        throw com::exception::device_not_found();
    }

    if (!isatty(m_fd)) {
        close_device();
        throw com::exception::invalid_device(device);
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
#undef VALID

    cfsetispeed(&m_options, m_termios_speed);
    cfsetospeed(&m_options, m_termios_speed);
}

void serial::check_and_set_data_size(unsigned int new_datasize)
{
#define VALID(value) case value: \
    m_options.c_cflag &= ~CSIZE; \
    m_options.c_cflag |= CS ## value; \
    break;
    switch (new_datasize)
    {
        VALID(5)
        VALID(6)
        VALID(7)
        VALID(8)
        default:
            throw com::exception::invalid_data_size(new_datasize);
    }
#undef VALID
}

void serial::check_and_set_stop_size(unsigned int new_stopsize)
{
    switch (new_stopsize)
    {
        case 1:
            m_options.c_cflag &= ~CSTOPB;
            break;
        case 2:
            m_options.c_cflag |= CSTOPB;
            break;
        default:
            throw com::exception::invalid_stop_size(new_stopsize);
    }
}

void serial::check_and_set_parity(char new_parity)
{
    switch (new_parity)
    {
        case 'n':
        case 'N':
            m_options.c_cflag &= ~PARENB;
            break;
        case 'o':
        case 'O':
            m_options.c_cflag |= PARENB;
            m_options.c_cflag |= PARODD;
            break;
        case 'e':
        case 'E':
            m_options.c_cflag |= PARENB;
            m_options.c_cflag &= ~PARODD;
            break;
        default:
            throw com::exception::invalid_parity(new_parity);
    }
}

void serial::commit_termios_configuration()
{
    if (tcsetattr(m_fd, TCSAFLUSH, &m_options) < 0)
        // Fail to apply configuration
        // This shall never happen due to all checks before
        throw exception::invalid_configuration();
}
