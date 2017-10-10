/**
* @file ccomserial.h
* @brief C API definitions
* @author Adrien Oliva
* @date 2017-10-10
*/
#ifndef CSERIALCOMM_H_CVLSDIF9
#define CSERIALCOMM_H_CVLSDIF9

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

#define COMSER_IOERROR                              (0x7fffffff)

/**
* @brief Opaque structure symbolizing a serial com device.
*/
struct comserial_s;

/**
* @brief Main type used in the whole libcomserial API.
*/
typedef struct comserial_s *comserial_t;

/**
* @brief Create and open a serial device given its path name.
*
* @param device Path to serial device to open and configure.
*
* @return Com Serial handle on the given device or NULL on error.
*
* By default, serial device is opened with the following configuration:
*   - speed set at 19200 bps
*   - data size set to 8 bits, without parity and 1 stop bit (8n1)
*   - read and write timeout are set to 1000 ms
*   .
*/
comserial_t comserial_create_device(const char *device);

/**
* @brief Destroy and clean memory after use of serial device.
*
* @param device Pointer to the device to clean.
*
* @note @em *device is set to NULL upon successful execution.
*/
void comserial_destroy_device(comserial_t *device);

unsigned int comserial_get_speed(const comserial_t device);
unsigned int comserial_set_speed(comserial_t device, unsigned int speed);

unsigned int comserial_get_data_size(const comserial_t device);
unsigned int comserial_set_data_size(comserial_t device, unsigned int data_size);

unsigned int comserial_get_stop_size(const comserial_t device);
unsigned int comserial_set_stop_size(comserial_t device, unsigned int stop_size);

char comserial_get_parity(const comserial_t device);
char comserial_set_parity(comserial_t device, char parity);

unsigned long comserial_get_read_timeout(const comserial_t device);
unsigned long comserial_set_read_timeout(comserial_t device, unsigned int parity);
unsigned long comserial_get_write_timeout(const comserial_t device);
unsigned long comserial_set_write_timeout(comserial_t device, unsigned int parity);

ssize_t comserial_write_buffer(const comserial_t device, const uint8_t *buffer, size_t length);
ssize_t comserial_read_buffer(const comserial_t device, uint8_t *buffer, size_t length);

#ifdef __cplusplus
};
#endif

#endif /* end of include guard: CSERIALCOMM_H_CVLSDIF9 */
