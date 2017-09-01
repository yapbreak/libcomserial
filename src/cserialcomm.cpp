#include "serialcomm/cserialcomm.h"
#include "serialcomm/cppserialcomm.h"

#include <cstdlib>

struct serialcomm_s {
    com::serial *dev;
};


serialcomm_t serialcomm_create_device(const char *device)
{
    (void) device;
    return NULL;
}

void serialcomm_destroy_device(serialcomm_t *device)
{
    (void) device;
}
