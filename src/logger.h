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
    class dump {
        public:
            dump(const void *data, const size_t size) : m_data(data)
                                                      , m_size(size)
            { }

            ~dump()
            { }

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
            const void *m_data;
            const size_t m_size;
    };

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
        log_location(const char *function,
                     const char *file,
                     const size_t line) : m_function(function)
                                        , m_file(file)
                                        , m_line(line)
        { }

        const std::string m_function;
        const std::string m_file;
        const size_t m_line;
    };

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

            // Additional overload to handle ostream specific IO manipulators
            friend InternalLog &operator<<(InternalLog &,
                                           std::ostream &(*)(std::ostream &));

        private:
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

            void print_header()
            {
                m_output << "[" << char_from_level(m_level) << "] "
                         << m_location.m_file << ":"
                         << m_location.m_line << "("
                         << m_location.m_function << ") ";
            }

        private:
            log_level m_level;
            log_location m_location;
            std::ostream &m_output;
    };

    template<typename T>
    inline InternalLog &operator<<(InternalLog &out, const T &value)
    {
        static_cast<std::ostream &>(out) << value;
        return out;
    }

    inline InternalLog &operator<<(InternalLog &out,
                                   std::ostream &(*f)(std::ostream &))
    {
        static_cast<std::ostream &>(out) << f;
        return out;
    }
};


#define FLOG() logger::InternalLog(logger::log_level::fatal, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)
#define ALOG() logger::InternalLog(logger::log_level::alert, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)
#define CLOG() logger::InternalLog(logger::log_level::crit, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)
#define ELOG() logger::InternalLog(logger::log_level::error, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)
#define WLOG() logger::InternalLog(logger::log_level::warn, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)
#define NLOG() logger::InternalLog(logger::log_level::notice, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)
#define ILOG() logger::InternalLog(logger::log_level::info, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)
#define DLOG() logger::InternalLog(logger::log_level::debug, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)
#define TLOG() logger::InternalLog(logger::log_level::trace, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   std::cerr)

#endif /* end of include guard: LOGGER_H_SOWJCIS8 */
