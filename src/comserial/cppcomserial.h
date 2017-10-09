#ifndef CPPSERIALCOMM_H_JSJEFHWR
#define CPPSERIALCOMM_H_JSJEFHWR

#include <comserial/exceptions.h>

#include <string>
#include <termios.h>

namespace com {

    class serial {

        public:
            serial(const std::string &device, unsigned int speed = 19200,
                                              unsigned int data_size = 8,
                                              unsigned int stop_size = 1,
                                              char parity = 'n');
            ~serial();

            unsigned int get_speed() const;
            unsigned int set_speed(unsigned int speed);

            unsigned int get_data_size() const;
            unsigned int set_data_size(unsigned int data_size);

            unsigned int get_stop_size() const;
            unsigned int set_stop_size(unsigned int stop_size);

            char get_parity() const;
            char set_parity(char parity);

            unsigned int get_read_timeout() const;
            unsigned int set_read_timeout(unsigned int timeout);
            unsigned int get_write_timeout() const;
            unsigned int set_write_timeout(unsigned int timeout);

            size_t write_buffer(const uint8_t *buffer, size_t length);
            size_t read_buffer(uint8_t *buffer, size_t length);

        private:
            void open_device(const char *device);
            void close_device();

            void check_and_set_speed(unsigned int new_speed);
            void check_and_set_data_size(unsigned int new_datasize);
            void check_and_set_stop_size(unsigned int new_stopsize);
            void check_and_set_parity(char new_parity);

            void commit_termios_configuration();


        private:
            int m_fd;
            unsigned int m_speed;
            unsigned int m_datasize;
            unsigned int m_stopsize;
            char m_parity;

            unsigned int m_read_timeout;
            unsigned int m_write_timeout;

            speed_t m_termios_speed;

            struct termios m_options;
    };

};

#endif /* end of include guard: CPPSERIALCOMM_H_JSJEFHWR */
