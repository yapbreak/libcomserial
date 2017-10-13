/**
* @file cppcomserial.h
* @brief API of C++ interface in libcomserial.
* @author Adrien Oliva
* @date 2017-10-13
*/
#ifndef CPPSERIALCOMM_H_JSJEFHWR
#define CPPSERIALCOMM_H_JSJEFHWR

#include <comserial/exceptions.h>

#include <string>
#include <termios.h>

namespace com {

    /**
    * @brief Main class at the heart of library, that provide RS-232 device
    *        abstraction.
    */
    class serial {

        public:
            /**
            * @brief Main object constructor to build a serial device instance.
            *
            * @param device Pathname of device to open.
            * @param speed Speed to set on the newly opened device (default to
            *        19200bps).
            * @param data_size Data size to set on the newly opened device
            *        (default to 8bits).
            * @param stop_size Stop size to set on the newly opened device
            *        (default to 1bit).
            * @param parity Parity to set on the newly opened device
            *        (default to none 'n').
            *
            * The following exception may occurs:
            *   - com::exception::invalid_speed when given speed is invalid.
            *   - com::exception::invalid_data_size when given data size is
            *     invalid.
            *   - com::exception::invalid_stop_size when given stop size is
            *     invalid.
            *   - com::exception::invalid_parity when given parity is invalid.
            *   - com::exception::device_not_found when given path name for
            *     device does not exists.
            *   - com::exception::invalid_device when given path is not a TTY.
            *   - com::exception::invalid_configuration when complete
            *     configuration failed to be set.
            *
            */
            serial(const std::string &device, unsigned int speed = 19200,
                                              unsigned int data_size = 8,
                                              unsigned int stop_size = 1,
                                              char parity = 'n');
            ~serial();

            /**
            * @brief Retrieve current speed set on device.
            *
            * @return Speed in bps.
            */
            unsigned int get_speed() const;
            /**
            * @brief Set a new speed to the device.
            *
            * @param speed New speed to set.
            *
            * @return Old speed set on device.
            *
            * The following exceptions may occur:
            *   - com::exception::invalid_speed when given speed is invalid.
            *   - com::exception::invalid_configuration when complete
            *     configuration failed to be set.
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
            */
            unsigned int set_speed(unsigned int speed);

            /**
            * @brief Retrieve current data size set on device.
            *
            * @return Data size in bits.
            */
            unsigned int get_data_size() const;
            /**
            * @brief Set a new data size to the device.
            *
            * @param data_size New data size to set.
            *
            * @return Old data size set on device.
            *
            * The following exceptions may occur:
            *   - com::exception::invalid_data_size when given data size is
            *     invalid.
            *   - com::exception::invalid_configuration when complete
            *     configuration failed to be set.
            *
            * Authorized value are:
            *   - 5
            *   - 6
            *   - 7
            *   - 8
            */
            unsigned int set_data_size(unsigned int data_size);

            /**
            * @brief Retrieve current stop size set on device.
            *
            * @return Stop size in bit(s).
            */
            unsigned int get_stop_size() const;
            /**
            * @brief Set a new stop size to the device.
            *
            * @param stop_size New stop size to set.
            *
            * @return Old stop size set on device.
            *
            * The following exceptions may occur:
            *   - com::exception::invalid_stop_size when given stop size is
            *     invalid.
            *   - com::exception::invalid_configuration when complete
            *     configuration failed to be set.
            *
            * Authorized value are:
            *   - 1
            *   - 2
            */
            unsigned int set_stop_size(unsigned int stop_size);

            /**
            * @brief Retrieve current parity set on device.
            *
            * @return parity in lower case ('n' for none, 'e' for even or
            *         'o' for odd)
            */
            char get_parity() const;
            /**
            * @brief Set a new parity to the device.
            *
            * @param parity New parity to set.
            *
            * @return Old parity set on device (in lower case).
            *
            * The following exceptions may occur:
            *   - com::exception::invalid_parity when given parity is invalid.
            *   - com::exception::invalid_configuration when complete
            *     configuration failed to be set.
            *
            * Authorized value are:
            *   - 'n' or 'N' for no parity
            *   - 'e' or 'E' for even parity
            *   - 'o' or 'O' for odd parity
            */
            char set_parity(char parity);

            /**
            * @brief Retrieve current read timeout set on device.
            *
            * @return Read timeout in ms.
            */
            unsigned int get_read_timeout() const;
            /**
            * @brief Set a new read timeout to the device.
            *
            * @param timeout New read timeout to set in ms.
            *
            * @return Old read timeout set on device in ms.
            */
            unsigned int set_read_timeout(unsigned int timeout);
            /**
            * @brief Retrieve current write timeout set on device.
            *
            * @return Write timeout in ms.
            */
            unsigned int get_write_timeout() const;
            /**
            * @brief Set a new write timeout to the device.
            *
            * @param timeout New write timeout to set in ms.
            *
            * @return Old write timeout set on device in ms.
            */
            unsigned int set_write_timeout(unsigned int timeout);

            /**
            * @brief Write a given data buffer on serial device.
            *
            * @param buffer Input data to write.
            * @param length Size of buffer to write.
            *
            * @return Total amount of byte(s) successfully written on device.
            *
            * The following exception may occur:
            *   - com::exception::invalid_input when input buffer is invalid
            *     (could be eigther a NULL pointer or a 0-length buffer)
            *   - com::exception::runtime_error when system call to select or
            *     write fail
            *   - com::exception::timeout when write timeout is reached.
            */
            size_t write_buffer(const uint8_t *buffer, size_t length);
            /**
            * @brief Read data on serial device.
            *
            * @param buffer Output buffer where read data is stored.
            * @param length Size of buffer to read
            *
            * @return Total amount of byte(s) successfully read on device.
            *
            * The following exception may occur:
            *   - com::exception::invalid_input when input buffer is invalid
            *     (could be eigther a NULL pointer or a 0-length buffer)
            *   - com::exception::runtime_error when system call to select or
            *     read fail
            *   - com::exception::timeout when read timeout is reached.
            */
            size_t read_buffer(uint8_t *buffer, size_t length);

        private:
            /**
            * @brief Really open device.
            *
            * @param device Path name of device to open.
            *
            * The following exception may occur:
            *   - com::exception::device_not_found if library is unable to open
            *     the given device (do not exists, insufficient permission…)
            *   - com::exception::invalid_device if the device is not a serial
            *     device (i.e. not a TTY).
            */
            void open_device(const char *device);
            /**
            * @brief Close any opened file descriptor inside instance.
            */
            void close_device();

            /**
            * @brief Validate and store new speed in object instance.
            *
            * @param new_speed Speed to validate.
            *
            * The following exception may occur:
            *   - com::exception::invalid_speed if given speed is invalid.
            */
            void check_and_set_speed(unsigned int new_speed);
            /**
            * @brief Validate and store new data size in object instance.
            *
            * @param new_datasize Data size to validate.
            *
            * The following exception may occur:
            *   - com::exception::invalid_data_size if given data size is
            *     invalid.
            */
            void check_and_set_data_size(unsigned int new_datasize);
            /**
            * @brief Validate and store new stop size in object instance.
            *
            * @param new_stopsize Stop size to validate.
            *
            * The following exception may occur:
            *   - com::exception::invalid_stop_size if given stop size is
            *     invalid.
            */
            void check_and_set_stop_size(unsigned int new_stopsize);
            /**
            * @brief Validate and store new parity in object instance.
            *
            * @param new_parity Parity to validate.
            *
            * The following exception may occur:
            *   - com::exception::invalid_parity if given parity is invalid.
            */
            void check_and_set_parity(char new_parity);

            /**
            * @brief Commit the whole stored configuration on the opened
            *        device.
            *
            * The following exception may occur:
            *   - com::exception::invalid_configuration() if global
            *     configuration is inconsistant.
            */
            void commit_termios_configuration();


        private:
            /**
            * @brief File descriptor of instance device.
            */
            int m_fd;
            /**
            * @brief Current speed (in bps).
            */
            unsigned int m_speed;
            /**
            * @brief Current data size (in bits).
            */
            unsigned int m_datasize;
            /**
            * @brief Current stop size (in bit(s)).
            */
            unsigned int m_stopsize;
            /**
            * @brief Current parity ('n', 'e' or 'o').
            */
            char m_parity;

            /**
            * @brief Current read timeout (in ms).
            */
            unsigned int m_read_timeout;
            /**
            * @brief Current write timeout (in ms).
            */
            unsigned int m_write_timeout;

            /**
            * @brief Termios version of current speed.
            */
            speed_t m_termios_speed;

            /**
            * @brief Termios structure with all serial options.
            */
            struct termios m_options;
    };

};

#endif /* end of include guard: CPPSERIALCOMM_H_JSJEFHWR */
