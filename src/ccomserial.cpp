#include "comserial/ccomserial.h"
#include "comserial/cppcomserial.h"

#include <cstdlib>

struct comserial_s {
    com::serial *dev;
};


comserial_t comserial_create_device(const char *device)
{
    struct comserial_s *serial;

    serial = new struct comserial_s;
    if (serial) {
        try {
            serial->dev = new com::serial(device);
        } catch (com::exception::device_not_found) {
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
        } catch (com::exception::invalid_speed) {
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
        } catch (com::exception::invalid_data_size) {
            old_data_size = 0;
        }
    }

    return old_data_size;
}
