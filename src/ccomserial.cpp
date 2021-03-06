/**
* @file ccomserial.cpp
* @brief Implementation of C interface of libcomserial.
* @author Adrien Oliva
* @date 2017-10-13
*/
#include "comserial/ccomserial.h"
#include "comserial/cppcomserial.h"

#include <cstdlib>

/**
* @brief Opaque structure symbolizing a serial com device.
*
* The structure is needed in C interface to encapsulate a com::serial object
* instance.
*/
struct comserial_s {
    /**
     * @brief Main C++ object instance.
     */
    com::serial *dev;
};


comserial_t comserial_create_device(const char *device)
{
    struct comserial_s *serial;

    serial = new struct comserial_s;
    if (serial) {
        try {
            serial->dev = new com::serial(device);
        } catch (com::exception::device_not_found &) {
            delete serial;
            serial = NULL;
        } catch (com::exception::invalid_device &) {
            delete serial;
            serial = NULL;
        }
    }

    return serial;
}

void comserial_destroy_device(comserial_t *device)
{
    if (device != NULL && (*device) != NULL) {
        delete (*device)->dev;
        delete (*device);
        (*device) = NULL;
    }
}

unsigned int comserial_get_speed(const comserial_t device)
{
    unsigned int speed = 0;

    if (device != NULL) {
        speed = device->dev->get_speed();
    }

    return speed;
}

unsigned int comserial_set_speed(comserial_t device, unsigned int speed)
{
    unsigned int old_speed = 0;

    if (device != NULL) {
        try {
            old_speed = device->dev->set_speed(speed);
        } catch (com::exception::invalid_speed &) {
            old_speed = 0;
        }
    }

    return old_speed;
}

unsigned int comserial_get_data_size(const comserial_t device)
{
    unsigned int data_size = 0;

    if (device != NULL)
        data_size = device->dev->get_data_size();

    return data_size;
}

unsigned int comserial_set_data_size(comserial_t device, unsigned int data_size)
{
    unsigned int old_data_size = 0;
    if (device != NULL) {
        try {
            old_data_size = device->dev->set_data_size(data_size);
        } catch (com::exception::invalid_data_size &) {
            old_data_size = 0;
        }
    }

    return old_data_size;
}

unsigned int comserial_get_stop_size(const comserial_t device)
{
    unsigned int stop_size = 0;

    if (device != NULL)
        stop_size = device->dev->get_stop_size();

    return stop_size;
}

unsigned int comserial_set_stop_size(comserial_t device, unsigned int stop_size)
{
    unsigned int old_stop_size = 0;
    if (device != NULL) {
        try {
            old_stop_size = device->dev->set_stop_size(stop_size);
        } catch (com::exception::invalid_stop_size &) {
            old_stop_size = 0;
        }
    }

    return old_stop_size;
}

char comserial_get_parity(const comserial_t device)
{
    char parity = 0;

    if (device != NULL)
        parity = device->dev->get_parity();

    return parity;
}

char comserial_set_parity(comserial_t device, char parity)
{
    unsigned int old_parity = 0;
    if (device != NULL) {
        try {
            old_parity = device->dev->set_parity(parity);
        } catch (com::exception::invalid_parity &) {
            old_parity = 0;
        }
    }

    return old_parity;
}

unsigned long comserial_get_read_timeout(const comserial_t device)
{
    unsigned int timeout = 0;

    if (device != NULL)
        timeout = device->dev->get_read_timeout();

    return timeout;
}

unsigned long comserial_set_read_timeout(comserial_t device, unsigned int timeout)
{
    unsigned int old_timeout = 0;

    if (device != NULL)
        old_timeout = device->dev->set_read_timeout(timeout);

    return old_timeout;
}

unsigned long comserial_get_write_timeout(const comserial_t device)
{
    unsigned int timeout = 0;

    if (device != NULL)
        timeout = device->dev->get_write_timeout();

    return timeout;
}

unsigned long comserial_set_write_timeout(comserial_t device, unsigned int timeout)
{
    unsigned int old_timeout = 0;

    if (device != NULL)
        old_timeout = device->dev->set_write_timeout(timeout);

    return old_timeout;
}

ssize_t comserial_write_buffer(const comserial_t device, const uint8_t *buffer, size_t length)
{
    ssize_t write_length = 0;

    if (device == NULL)
        return -COMSER_IOERROR;

    try {
        write_length = device->dev->write_buffer(buffer, length);
    } catch (com::exception::invalid_input &) {
        return -COMSER_IOERROR;
    } catch (com::exception::runtime_error &) {
        return -COMSER_IOERROR;
    } catch (const com::exception::timeout &e) {
        return -e.get_bytes();
    }

    return write_length;
}

ssize_t comserial_read_buffer(const comserial_t device, uint8_t *buffer, size_t length)
{
    ssize_t read_length = 0;

    if (device == NULL)
        return -COMSER_IOERROR;

    try {
        read_length = device->dev->read_buffer(buffer, length);
    } catch (com::exception::invalid_input &) {
        return -COMSER_IOERROR;
    } catch (com::exception::runtime_error &) {
        return -COMSER_IOERROR;
    } catch (const com::exception::timeout &e) {
        return -e.get_bytes();
    }

    return read_length;
}

