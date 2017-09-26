#ifndef CPPSERIALCOMM_H_JSJEFHWR
#define CPPSERIALCOMM_H_JSJEFHWR

#include <comserial/exceptions.h>

#include <string>
#include <termios.h>

namespace com {

    class serial {

        public:
            serial(const std::string &device, unsigned int speed = 19200);
            ~serial();

            unsigned int get_speed() const;
            unsigned int set_speed(unsigned int speed);

        private:
            void open_device(const char *device);
            void close_device();

            void check_and_set_speed(unsigned int new_speed);

            void commit_termios_configuration();


        private:
            int m_fd;
            unsigned int m_speed;

            speed_t m_termios_speed;

            struct termios m_options;
    };

};

#endif /* end of include guard: CPPSERIALCOMM_H_JSJEFHWR */
