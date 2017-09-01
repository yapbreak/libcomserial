#ifndef CPPSERIALCOMM_H_JSJEFHWR
#define CPPSERIALCOMM_H_JSJEFHWR

#include <comserial/exceptions.h>

#include <string>

namespace com {

    class serial {

        public:
            explicit serial(const std::string &device);
            ~serial();


        private:
            void open_device(const char *device);
            void close_device();


        private:
            int m_fd;
    };

};

#endif /* end of include guard: CPPSERIALCOMM_H_JSJEFHWR */
