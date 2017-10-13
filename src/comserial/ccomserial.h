/**
* @file ccomserial.h
* @brief API of C interface in libcomserial.
* @author Adrien Oliva
* @date 2017-10-13
*/
#ifndef CSERIALCOMM_H_CVLSDIF9
#define CSERIALCOMM_H_CVLSDIF9

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

/**
* @brief Generic I/O error code.
*/
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

/**
* @brief Retrieve current speed set on device.
*
* @param device Requested device.
*
* @return Speed in bps or 0 if given device is invalid.
*/
unsigned int comserial_get_speed(const comserial_t device);
/**
* @brief Set a new speed on given device.
*
* @param device Requested device.
* @param speed New speed to set.
*
* Authorized value are:
*   - 50
*   - 75
*   - 110
*   - 134
*   - 150
*   - 200
*   - 300
*   - 600
*   - 1200
*   - 1800
*   - 2400
*   - 4800
*   - 9600
*   - 19200
*   - 38400
*   - 57600
*   - 115200
*   - 230400
*
* @return Old speed of device or 0 on error (invalid speed or invalid device).
*/
unsigned int comserial_set_speed(comserial_t device, unsigned int speed);

/**
* @brief Retrieve current data size set on device.
*
* @param device Requested device.
*
* @return Data size in bits or 0 if given device is invalid.
*/
unsigned int comserial_get_data_size(const comserial_t device);
/**
* @brief Set a new data size on given device.
*
* @param device Requested device.
* @param data_size New data size to set.
*
* Authorized value are:
*   - 5
*   - 6
*   - 7
*   - 8
*
* @return Old data size of device or 0 on error (invalid data size or
*         invalid device).
*/
unsigned int comserial_set_data_size(comserial_t device, unsigned int data_size);

/**
* @brief Retrieve current stop size set on device.
*
* @param device Requested device.
*
* @return Stop size in bits or 0 if given device is invalid.
*/
unsigned int comserial_get_stop_size(const comserial_t device);
/**
* @brief Set a new stop size on given device.
*
* @param device Requested device.
* @param stop_size New stop size to set.
*
* Authorized value are:
*   - 1
*   - 2
*
* @return Old stop size of device or 0 on error (invalid stop size or
*         invalid device).
*/
unsigned int comserial_set_stop_size(comserial_t device, unsigned int stop_size);

/**
* @brief Retrieve current parity set on device.
*
* @param device Requested device.
*
* @return parity in lower case ('n' for none, 'e' for even or 'o' for odd) or
*         0 if given device is invalid.
*/
char comserial_get_parity(const comserial_t device);
/**
* @brief Set a new parity on given device.
*
* @param device Requested device.
* @param parity New parity to set.
*
* Authorized value are:
*   - 'n' or 'N' for no parity
*   - 'e' or 'E' for even parity
*   - 'o' or 'O' for odd parity
*
* @return Old parity (in lower case) of device or 0 on error (invalid parity or
*         invalid device).
*/
char comserial_set_parity(comserial_t device, char parity);

/**
* @brief Retrieve the current read timeout registered in device.
*
* @param device Requested device.
*
* @return current read timeout in ms, or 0 if given device is invalid.
*/
unsigned long comserial_get_read_timeout(const comserial_t device);
/**
* @brief Set a new read timeout for the subsequent read call on serial device.
*
* @param device Requested device.
* @param timeout New read timeout to apply (in ms).
*
* @return Old read timeout of device or 0 on error (invalid device).
*/
unsigned long comserial_set_read_timeout(comserial_t device, unsigned int timeout);
/**
* @brief Retrieve the current write timeout registered in device.
*
* @param device Requested device.
*
* @return current write timeout in ms, or 0 if given device is invalid.
*/
unsigned long comserial_get_write_timeout(const comserial_t device);
/**
* @brief Set a new write timeout for the subsequent write call on serial device.
*
* @param device Requested device.
* @param timeout New write timeout to apply (in ms).
*
* @return Old write timeout of device or 0 on error (invalid device).
*/
unsigned long comserial_set_write_timeout(comserial_t device, unsigned int timeout);

/**
* @brief Write a given data buffer on serial device.
*
* @param device Device where data will be written.
* @param buffer Input data to write.
* @param length Size of buffer to write.
*
* @return Total amount of byte(s) successfully written on device. On error, a
*         negative value is returned and could be -COMSER_IOERROR for a generic
*         write error, or a value in range [-1, -length[ in case of timeout
*         (with the opposite of bytes really written).
*
*/
ssize_t comserial_write_buffer(const comserial_t device, const uint8_t *buffer, size_t length);
/**
* @brief Read a given data buffer on serial device.
*
* @param device Device where data will be written.
* @param buffer Output buffer where read data is stored.
* @param length Size of buffer to read.
*
* @return Total amount of byte(s) successfully read on device. On error, a
*         negative value is returned and could be -COMSER_IOERROR for a generic
*         read error, or a value in range [-1, -length[ in case of timeout
*         (with the opposite of bytes really read).
*
*/
ssize_t comserial_read_buffer(const comserial_t device, uint8_t *buffer, size_t length);

#ifdef __cplusplus
};
#endif

#endif /* end of include guard: CSERIALCOMM_H_CVLSDIF9 */
