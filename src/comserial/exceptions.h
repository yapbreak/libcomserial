/**
* @file exceptions.h
* @brief Group all exceptions of library.
* @author Adrien Oliva
* @date 2017-10-13
*/
#ifndef EXCEPTIONS_H_OZFRKXV6
#define EXCEPTIONS_H_OZFRKXV6

#include <exception>
#include <sstream>

namespace com
{

    namespace exception
    {

        /**
        * @brief Exception thrown when an invalid device is given.
        */
        class device_not_found : public std::exception
        {
            public:
                /**
                * @brief Get exception error message.
                *
                * @return Error message.
                */
                virtual const char *what() const throw() {
                    return "Device not found";
                };
        };

        /**
        * @brief Exception thrown when an invalid speed is given.
        *
        * The given speed is shown in the exception message.
        */
        class invalid_speed : public std::exception
        {
            public:
                /**
                * @brief Constructor of an invalid speed exception.
                *
                * @param speed Invalid speed that cause the exception.
                */
                explicit invalid_speed(unsigned int speed) : m_what() {
                    std::stringstream ss;
                    ss << "Invalid speed (" << speed << ")";
                    m_what.assign(ss.str());
                }

                /**
                * @brief Get exception error message.
                *
                * @return Error message.
                */
                virtual const char *what() const throw() {
                    return m_what.c_str();
                }

            private:
                /**
                * @brief Exception error message.
                */
                std::string m_what;
        };

        /**
        * @brief Exception thrown when an invalid configuration is set in
        *        the underlying termios device.
        *
        * @note This exception exists for code completeness but should not
        *       be raised due to many other control made before.
        */
        class invalid_configuration : public std::exception
        {
            public:
                /**
                * @brief Get exception error message.
                *
                * @return Error message.
                */
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
                /**
                * @brief Constructor of an invalid data size exception.
                *
                * @param data_size Invalid data size that cause the exception.
                */
                explicit invalid_data_size(unsigned int data_size) : m_what() {
                    std::stringstream ss;
                    ss << "Invalid data size (" << data_size << ")";
                    m_what.assign(ss.str());
                }

                /**
                * @brief Get exception error message.
                *
                * @return Error message.
                */
                virtual const char *what() const throw() {
                    return m_what.c_str();
                }

            private:
                /**
                * @brief Exception error message.
                */
                std::string m_what;
        };

        /**
        * @brief Exception thrown when an invalid stop size value is given to
        *         a serial device.
        *
        * The given stop size is shown in exception message.
        */
        class invalid_stop_size : public std::exception
        {
            public:
                /**
                * @brief Constructor of an invalid stop size exception.
                *
                * @param stop_size Invalid stop size that cause the exception.
                */
                explicit invalid_stop_size(unsigned int stop_size) : m_what() {
                    std::stringstream ss;
                    ss << "Invalid stop size (" << stop_size << ")";
                    m_what.assign(ss.str());
                }

                /**
                * @brief Get exception error message.
                *
                * @return Error message.
                */
                virtual const char *what() const throw() {
                    return m_what.c_str();
                }

            private:
                /**
                * @brief Exception error message.
                */
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
                /**
                * @brief Constructor of an invalid parity exception.
                *
                * @param parity Invalid parity that cause the exception.
                */
                explicit invalid_parity(char parity) : m_what() {
                    std::stringstream ss;
                    ss << "Invalid parity (" << parity << ")";
                    m_what.assign(ss.str());
                }

                /**
                * @brief Get exception error message.
                *
                * @return Error message.
                */
                virtual const char *what() const throw() {
                    return m_what.c_str();
                }

            private:
                /**
                * @brief Exception error message.
                */
                std::string m_what;
        };

        /**
        * @brief Exception thrown when given device path is invalid.
        *
        * The given device is shown in exception message.
        */
        class invalid_device : public std::exception
        {
            public:
                /**
                * @brief Constructor of an invalid device exception.
                *
                * @param device Invalid device that cause the exception.
                */
                explicit invalid_device(const char *device) : m_what() {
                    std::stringstream ss;
                    ss << "Invalid device (" << device << ")";
                    m_what.assign(ss.str());
                }

                /**
                * @brief Get exception error message.
                *
                * @return Error message.
                */
                virtual const char *what() const throw() {
                    return m_what.c_str();
                }

            private:
                /**
                * @brief Exception error message.
                */
                std::string m_what;
        };

        /**
        * @brief Exception thrown when an invalid argument is given to any
        *        function.
        */
        class invalid_input : public std::exception
        {
            public:
                /**
                * @brief Get exception error message.
                *
                * @return Error message.
                */
                virtual const char *what() const throw() {
                    return "Invalid argument";
                };
        };

        /**
        * @brief Exception thrown on device timeout.
        *
        * The exception contains the number of byte read or write before
        * timeout occurs.
        */
        class timeout: public std::exception
        {
            public:
                /**
                * @brief Constructor of a timeout exception.
                *
                * @param bytes Number of bytes read before timeout occurs.
                */
                explicit timeout(size_t bytes = 0): m_bytes(bytes) {
                }

                /**
                * @brief Get exception error message.
                *
                * @return Error message.
                */
                virtual const char *what() const throw() {
                    return "Timeout reached";
                }

                /**
                * @brief Retrieve the number of byte read just before exception
                *        occurs.
                *
                * @return Number of bytes.
                */
                size_t get_bytes() const {
                    return m_bytes;
                }

            private:
                /**
                * @brief Exception error message.
                */
                const size_t m_bytes;
        };

        /**
        * @brief Exception thrown on generic runtime error.
        *
        * More information in exception message.
        */
        class runtime_error: public std::exception
        {
            public:
                /**
                * @brief Constructor of a runtime error exception.
                *
                * @param message Extra information of runtime error.
                */
                explicit runtime_error(const char *message) : m_what() {
                    std::stringstream ss;
                    ss << "Runtime error: " << message;
                    m_what.assign(ss.str());
                }

                /**
                * @brief Get exception error message.
                *
                * @return Error message.
                */
                virtual const char *what() const throw() {
                    return m_what.c_str();
                }

            private:
                /**
                * @brief Exception error message.
                */
                std::string m_what;
        };

    };

};

#endif /* end of include guard: EXCEPTIONS_H_OZFRKXV6 */
