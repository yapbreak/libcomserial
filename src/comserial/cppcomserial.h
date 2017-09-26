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
                                              unsigned int stop_size = 1);
            ~serial();

            unsigned int get_speed() const;
            unsigned int set_speed(unsigned int speed);

            unsigned int get_data_size() const;
            unsigned int set_data_size(unsigned int data_size);

            unsigned int get_stop_size() const;
            unsigned int set_stop_size(unsigned int stop_size);

        private:
            void open_device(const char *device);
            void close_device();

            void check_and_set_speed(unsigned int new_speed);
            void check_and_set_data_size(unsigned int new_datasize);
            void check_and_set_stop_size(unsigned int new_stopsize);

            void commit_termios_configuration();


        private:
            int m_fd;
            unsigned int m_speed;
            unsigned int m_datasize;
            unsigned int m_stopsize;

            speed_t m_termios_speed;

            struct termios m_options;
    };

};

#endif /* end of include guard: CPPSERIALCOMM_H_JSJEFHWR */
