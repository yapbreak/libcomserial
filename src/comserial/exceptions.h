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

        /**
        * @brief Exception thrown when an invalid data size value is given to
        *         a serial device.
        *
        * The given data size is shown in exception message.
        */
        class invalid_data_size : public std::exception
        {
            public:
                explicit invalid_data_size(unsigned int data_size) : m_what() {
                    std::stringstream ss;
                    ss << "Invalid data size (" << data_size << ")";
                    m_what.assign(ss.str());
                }

                virtual const char *what() const throw() {
                    return m_what.c_str();
                }

            private:
                std::string m_what;
        };

        class invalid_stop_size : public std::exception
        {
            public:
                explicit invalid_stop_size(unsigned int stop_size) : m_what() {
                    std::stringstream ss;
                    ss << "Invalid stop size (" << stop_size << ")";
                    m_what.assign(ss.str());
                }

                virtual const char *what() const throw() {
                    return m_what.c_str();
                }

            private:
                std::string m_what;
        };

        /**
        * @brief Exception thrown when an invalid parity value is given to a
        *        serial device.
        *
        * The given parity is shown in exception message.
        */
        class invalid_parity : public std::exception
        {
            public:
                explicit invalid_parity(char parity) : m_what() {
                    std::stringstream ss;
                    ss << "Invalid parity (" << parity << ")";
                    m_what.assign(ss.str());
                }

                virtual const char *what() const throw() {
                    return m_what.c_str();
                }

            private:
                std::string m_what;
        };

        class invalid_device : public std::exception
        {
            public:
                explicit invalid_device(const char *device) : m_what() {
                    std::stringstream ss;
                    ss << "Invalid device (" << device << ")";
                    m_what.assign(ss.str());
                }

                virtual const char *what() const throw() {
                    return m_what.c_str();
                }

            private:
                std::string m_what;
        };

        /**
        * @brief Exception thrown when an invalid argument is given to any
        *        function.
        */
        class invalid_input : public std::exception
        {
            public:
                virtual const char *what() const throw() {
                    return "Invalid argument";
                };
        };

        class timeout: public std::exception
        {
            public:
                explicit timeout(size_t bytes = 0): m_bytes(bytes) {
                }

                virtual const char *what() const throw() {
                    return "Timeout reached";
                }

                size_t get_bytes() const {
                    return m_bytes;
                }

            private:
                const size_t m_bytes;
        };

        class runtime_error: public std::exception
        {
            public:
                explicit runtime_error(const char *message) : m_what() {
                    std::stringstream ss;
                    ss << "Runtime error: " << message;
                    m_what.assign(ss.str());
                }

                virtual const char *what() const throw() {
                    return m_what.c_str();
                }

            private:
                std::string m_what;
        };

    };

};

#endif /* end of include guard: EXCEPTIONS_H_OZFRKXV6 */
