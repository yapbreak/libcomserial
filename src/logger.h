/**
* @file logger.h
* @brief Define helper class to print log on stderr, mainly for debug purpose.
* @author Adrien Oliva
* @date 2017-10-10
*/
#ifndef LOGGER_H_SOWJCIS8
#define LOGGER_H_SOWJCIS8

#include <ostream>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <unistd.h>

namespace logger {
    /**
    * @brief Allow a human readable representation of a data buffer
    *
    * The purpose of this class is to format a given buffer into a string
    * similar to the output of `hexdump -Cv`, with data offset, hexadecimal
    * representation and ascii representation.
    */
    class dump {
        public:
            /**
            * @brief Create a human readable representation of a given buffer.
            *
            * @param data Object based buffer.
            * @param size Size of data buffer.
            */
            dump(const void *data, const size_t size) : m_data(data)
                                                      , m_size(size)
            { }

            ~dump()
            { }

            /**
            * @brief Retrieve human readable version of buffer.
            *
            * @return Human readable string.
            */
            std::string get_formatted_string() const
            {
                const unsigned char *data_ptr =
                                    static_cast<const unsigned char *>(m_data);

                std::stringstream output;
                output << "Dump " << m_size
                       << " byte(s) starting at " << m_data << ":";

                std::stringstream offset;
                std::stringstream hexa;
                std::stringstream ascii;

                size_t i = 0;

                for (i = 0; i < m_size; i++) {
                    if (i % 16 == 0) {
                        output << "\n";
                        offset.str("");
                        offset << std::setw(8) << std::setfill('0')
                               << std::hex << i;
                        offset << " ";
                        hexa.str("");
                        ascii.str("");
                    }

                    // Add one extra space after 8 bytes.
                    if (i % 16 == 8) {
                        ascii << " ";
                        hexa << " ";
                    }

                    hexa << std::hex << std::setfill('0') << std::setw(2)
                         << static_cast<unsigned int>(*data_ptr);
                    hexa << " ";

                    if (isprint(*data_ptr))
                        ascii << (*data_ptr);
                    else
                        ascii << ".";

                    data_ptr++;

                    if (i % 16 == 15) {
                        output << offset.str() << hexa.str()
                               << "|" << ascii.str() << "|";
                    }
                }

                return output.str();
            }

        private:
            /**
            * @brief Pointer to linked data in instance.
            */
            const void *m_data;
            /**
            * @brief Size of buffer.
            */
            const size_t m_size;
    };

    /**
    * @brief Allow to print a dump object instance through std::ostream
    *        instance.
    *
    * @param out Stream where object will be printed.
    * @param data Data to print.
    *
    * @return Reference to the used output stream.
    */
    inline std::ostream &operator<<(std::ostream &out, const dump &data)
    {
        out << data.get_formatted_string();
        return out;
    }

    /**
    * @brief Contains all information needed to localize a given point in
    *        codebase.
    *
    * This structure especially retains current function name, current file
    * and current line.
    */
    struct log_location {
        /**
        * @brief Build a location structure with function file and line
        *        information.
        *
        * @param function Function name.
        * @param file File name.
        * @param line Line number.
        */
        log_location(const char *function,
                     const char *file,
                     const size_t line) : m_function(function)
                                        , m_file(file)
                                        , m_line(line)
        { }

        /**
        * @brief Function name.
        */
        const std::string m_function;
        /**
        * @brief File name.
        */
        const std::string m_file;
        /**
        * @brief Line number.
        */
        const size_t m_line;
    };

    /**
    * @brief Define different level of logs.
    */
    enum log_level {
        fatal,
        alert,
        crit,
        error,
        warn,
        notice,
        info,
        debug,
        trace,
    };

    /**
    * @brief Main class that allow logging to a given ostream destination.
    */
    class InternalLog: public std::ostream
    {
        public:
            /**
            * @brief Contructor of a simple logger, linked to any standard
            *        output stream.
            *
            * @param level The log level of the given logger.
            * @param loc Information of location of log in code base.
            * @param destination Standard output stream to be used.
            */
            InternalLog(log_level level, const log_location &loc,
                        std::ostream &destination)
                : std::ostream(destination.rdbuf())
                , m_level(level)
                , m_location(loc)
                , m_output(destination)
            {
                print_header();
            }

            virtual ~InternalLog()
            {
                *this << "\n";
            }

            template<typename T>
            friend InternalLog &operator<<(InternalLog &, const T &);

            /**
            * @brief Additional overload to handle ostream specific IO
            *         manipulators
            *
            * @param out Internal logger where IO manipulators must aplly.
            * @param f IO function manipulators.
            *
            * @return Internal logger instance.
            */
            friend InternalLog &operator<<(InternalLog &out,
                                           std::ostream &(*f)(std::ostream &));

        private:
            /**
            * @brief Convert a log level to a single character.
            *
            * @param l Loglevel to convert.
            *
            * @return Single character symbolizes log level.
            */
            char char_from_level(enum log_level l)
            {
                switch (l) {
                    case fatal:
                        return 'F';
                    case alert:
                        return 'A';
                    case crit:
                        return 'C';
                    case error:
                        return 'E';
                    case warn:
                        return 'W';
                    case notice:
                        return 'N';
                    case info:
                        return 'I';
                    case debug:
                        return 'D';
                    case trace:
                        return 'T';
                    default:
                        return ' ';
                }
            }

            /**
            * @brief Prepare and print log prefix.
            *
            * Any log use the following prefix:
            * - "[X] file:line(function) "
            *
            * where:
            *   - X is one of the following character ('F' for fatal, 'A' for
            *     alert, 'C' for critical, 'E' for error, 'W' for warning, 'N'
            *     for notice, 'I' for information, 'D' for debug, 'T' for trace
            *     or a space for any other level.
            *   - file is the name of the file where log append.
            *   - line is the line number where log append.
            *   - function is the function name where log append.
            */
            void print_header()
            {
                m_output << "[" << char_from_level(m_level) << "] "
                         << m_location.m_file << ":"
                         << m_location.m_line << "("
                         << m_location.m_function << ") ";
            }

        private:
            /**
            * @brief Log level.
            */
            log_level m_level;
            /**
            * @brief Log location.
            */
            log_location m_location;
            /**
            * @brief Linked output stream.
            */
            std::ostream &m_output;
    };

    /**
    * @brief Print any type to an internal logger instance.
    *
    * @tparam T Typename of data to print
    * @param out Internal logger instance where data will be printed
    * @param value Data to print
    *
    * @return Internal logger instance used.
    */
    template<typename T>
    inline InternalLog &operator<<(InternalLog &out, const T &value)
    {
        static_cast<std::ostream &>(out) << value;
        return out;
    }

    /**
    * @brief Allow use of stream modifier to an internal logger instance.
    *
    * @param out Internal logger instance where data will be printed
    * @param f Stream modifier function
    *
    * @return Internal logger instance used.
    */
    inline InternalLog &operator<<(InternalLog &out,
                                   std::ostream &(*f)(std::ostream &))
    {
        static_cast<std::ostream &>(out) << f;
        return out;
    }
};


/**
 * @brief Fatal log macro utility to print a fatal message on stderr.
 */
#define FLOG() logger::InternalLog(logger::log_level::fatal, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)
/**
 * @brief Alert log macro utility to print an alert message on stderr.
 */
#define ALOG() logger::InternalLog(logger::log_level::alert, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)
/**
 * @brief Critical log macro utility to print a critical message on stderr.
 */
#define CLOG() logger::InternalLog(logger::log_level::crit, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)
/**
 * @brief Error log macro utility to print an error message on stderr.
 */
#define ELOG() logger::InternalLog(logger::log_level::error, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)
/**
 * @brief Warning log macro utility to print a warning message on stderr.
 */
#define WLOG() logger::InternalLog(logger::log_level::warn, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)
/**
 * @brief Notice log macro utility to print a notice message on stderr.
 */
#define NLOG() logger::InternalLog(logger::log_level::notice, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)
/**
 * @brief Information log macro utility to print an information message on
 *        stderr.
 */
#define ILOG() logger::InternalLog(logger::log_level::info, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)
/**
 * @brief Debug log macro utility to print a debug message on stderr.
 */
#define DLOG() logger::InternalLog(logger::log_level::debug, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)
/**
 * @brief Trace log macro utility to print a trace message on stderr.
 */
#define TLOG() logger::InternalLog(logger::log_level::trace, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)

#endif /* end of include guard: LOGGER_H_SOWJCIS8 */
