#include "comserial/ccomserial.h"
#include "comserial/cppcomserial.h"

#include <cstdlib>

struct comserial_s {
    com::serial *dev;
};


comserial_t comserial_create_device(const char *device)
{
    (void) device;
    return NULL;
}

void comserial_destroy_device(comserial_t *device)
{
    (void) device;
}
