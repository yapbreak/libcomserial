/**
* @file cppcomserial.cpp
* @brief C++ implementation of com::serial.
* @author Adrien Oliva
* @date 2017-10-13
*/
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
    , m_read_timeout(1000)
    , m_write_timeout(1000)
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

    NLOG() << "New serial device " << device;
    ILOG() << "@" << speed << "bps, "
                  << data_size
                  << parity
                  << stop_size;
}

serial::~serial()
{
    ILOG() << "Destroy device";
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

    ILOG() << "New speed set: " << old_speed << " -> " << m_speed;

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

    ILOG() << "New data size set: " << old_datasize << " -> " << m_datasize;
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

    ILOG() << "New stop size set: " << old_stopsize << " -> " << m_stopsize;
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

    ILOG() << "New parity set: " << old_parity << " -> " << m_parity;
    return old_parity;
}

unsigned int serial::get_read_timeout() const
{
    return m_read_timeout;
}

unsigned int serial::set_read_timeout(unsigned int timeout)
{
    unsigned int old_timeout = m_read_timeout;

    m_read_timeout = timeout;

    ILOG() << "New read timeout: " << old_timeout << " -> " << m_read_timeout;
    return old_timeout;
}

unsigned int serial::get_write_timeout() const
{
    return m_write_timeout;
}

unsigned int serial::set_write_timeout(unsigned int timeout)
{
    unsigned int old_timeout = m_write_timeout;

    m_write_timeout = timeout;

    ILOG() << "New write timeout: " << old_timeout << " -> " << m_write_timeout;
    return old_timeout;
}

size_t serial::write_buffer(const uint8_t *buffer, size_t length)
{
    if (buffer == NULL || length == 0) {
        ELOG() << "Invalid buffer to write";
        throw exception::invalid_input();
    }

    size_t size_written = 0;

    fd_set write_set;
    struct timeval tv = { m_write_timeout / 1000,
                          (m_write_timeout % 1000) * 1000 };

    FD_ZERO(&write_set);
    FD_SET(m_fd, &write_set);

    while (size_written != length) {
        int ret = select(m_fd + 1, NULL, &write_set, NULL, &tv);
        if (ret < 0) {
            CLOG() << "Internal system function returns error (select)";
            throw exception::runtime_error("Fail to select");
        } else if (ret != 0) {
            if (FD_ISSET(m_fd, &write_set)) {
                ssize_t w = write(m_fd, buffer + size_written,
                                        length - size_written);
                if (w < 0) {
                    ALOG() << "Fail to write buffer";
                    throw exception::runtime_error("Fail to write");
                }

                size_written += w;
            }
        } else {
            WLOG() << "Timeout error";
            throw exception::timeout(size_written);
        }
    }

    DLOG() << "Write success:" << logger::dump(buffer, length);

    return size_written;
}

size_t serial::read_buffer(uint8_t *buffer, size_t length)
{
    if (buffer == NULL || length == 0)
        throw exception::invalid_input();

    size_t size_read = 0;

    fd_set read_set;
    struct timeval tv = { m_read_timeout / 1000,
                          (m_read_timeout % 1000) * 1000 };

    FD_ZERO(&read_set);
    FD_SET(m_fd, &read_set);

    while (size_read != length) {
        int ret = select(m_fd + 1, &read_set, NULL, NULL, &tv);
        if (ret < 0) {
            CLOG() << "Internal system function returns error (select)";
            throw exception::runtime_error("Fail to select");
        } else if (ret != 0) {
            if (FD_ISSET(m_fd, &read_set)) {
                ssize_t r = read(m_fd, buffer + size_read,
                                       length - size_read);
                if (r < 0) {
                    ALOG() << "Fail to read buffer";
                    throw exception::runtime_error("Fail to read");
                } else if (r == 0) {
                    WLOG() << "Timeout error";
                    DLOG() << "Read only:" << logger::dump(buffer, size_read);
                    throw exception::timeout(size_read);
                }

                size_read += r;
            }
        } else {
            throw exception::timeout(size_read);
        }
    }

    DLOG() << "Read success:" << logger::dump(buffer, size_read);
    return size_read;
}

void serial::open_device(const char *device)
{
    m_fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY | O_SYNC);
    if (m_fd < 0) {
        m_fd = -1;
        FLOG() << device << " not found";
        throw com::exception::device_not_found();
    }

    if (!isatty(m_fd)) {
        close_device();
        FLOG() << device << " not a serial device";
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
    switch (new_speed) {
        case 50:
            m_termios_speed = B50;
            break;
        case 75:
            m_termios_speed = B75;
            break;
        case 110:
            m_termios_speed = B110;
            break;
        case 134:
            m_termios_speed = B134;
            break;
        case 150:
            m_termios_speed = B150;
            break;
        case 200:
            m_termios_speed = B200;
            break;
        case 300:
            m_termios_speed = B300;
            break;
        case 600:
            m_termios_speed = B600;
            break;
        case 1200:
            m_termios_speed = B1200;
            break;
        case 1800:
            m_termios_speed = B1800;
            break;
        case 2400:
            m_termios_speed = B2400;
            break;
        case 4800:
            m_termios_speed = B4800;
            break;
        case 9600:
            m_termios_speed = B9600;
            break;
        case 19200:
            m_termios_speed = B19200;
            break;
        case 38400:
            m_termios_speed = B38400;
            break;
        case 57600:
            m_termios_speed = B57600;
            break;
        case 115200:
            m_termios_speed = B115200;
            break;
        case 230400:
            m_termios_speed = B230400;
            break;
        default:
            ELOG() << new_speed << " is not a valid speed";
            throw com::exception::invalid_speed(new_speed);
    }

    cfsetispeed(&m_options, m_termios_speed);
    cfsetospeed(&m_options, m_termios_speed);
}

void serial::check_and_set_data_size(unsigned int new_datasize)
{
    switch (new_datasize)
    {
        case 5:
            m_options.c_cflag &= ~CSIZE;
            m_options.c_cflag |= CS5;
            break;
        case 6:
            m_options.c_cflag &= ~CSIZE;
            m_options.c_cflag |= CS6;
            break;
        case 7:
            m_options.c_cflag &= ~CSIZE;
            m_options.c_cflag |= CS7;
            break;
        case 8:
            m_options.c_cflag &= ~CSIZE;
            m_options.c_cflag |= CS8;
            break;
        default:
            ELOG() << new_datasize << " is not a valid data size";
            throw com::exception::invalid_data_size(new_datasize);
    }
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
            ELOG() << new_stopsize << " is not a valid stop size";
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
            ELOG() << new_parity << " is not a valid parity";
            throw com::exception::invalid_parity(new_parity);
    }
}

void serial::commit_termios_configuration()
{
    if (tcsetattr(m_fd, TCSAFLUSH, &m_options) < 0) {
        // Fail to apply configuration
        // This shall never happen due to all checks before
        ALOG() << "Inconsistant configuration";
        throw exception::invalid_configuration();
    }
}
