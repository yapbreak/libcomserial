#ifndef EXCEPTIONS_H_OZFRKXV6
#define EXCEPTIONS_H_OZFRKXV6

#include <exception>
#include <sstream>

namespace com
{

    namespace exception
    {

        class device_not_found : public std::exception
        {
            public:
                virtual const char *what() const throw() {
                    return "Device not found";
                };
        };

        class invalid_speed : public std::exception
        {
            public:
                explicit invalid_speed(unsigned int speed) : m_what() {
                    std::stringstream ss;
                    ss << "Invalid speed (" << speed << ")";
                    m_what.assign(ss.str());
                }

                virtual const char *what() const throw() {
                    return m_what.c_str();
                }

            private:
                std::string m_what;
        };

        class invalid_configuration : public std::exception
        {
            public:
                virtual const char *what() const throw() {
                    return "Invalid configuration set";
                };
        };

    };

};

#endif /* end of include guard: EXCEPTIONS_H_OZFRKXV6 */
