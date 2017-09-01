#include "serialcomm/cserialcomm.h"

#include <stdio.h>
#include <stdlib.h>

struct serialcomm_s {
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
