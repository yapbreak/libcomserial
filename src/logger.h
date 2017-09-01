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
                unsigned char *data_ptr = (unsigned char *) m_data;

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
                         << (unsigned int) (*data_ptr);
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

                if (i % 16 != 0) {
                    output << offset.str();
                    output << std::setfill(' ') << std::setw(49)
                           << std::left << hexa.str();
                    output << "|";
                    output << std::setfill(' ') << std::setw(17)
                           << std::left << ascii.str();
                    output << "|";
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

    template<std::ostream &C>
    class InternalLog: public std::ostream
    {
        public:
            InternalLog(log_level level, const log_location &loc)
                : std::ostream(C.rdbuf())
                , m_level(level)
                , m_location(loc)
            {
                print_header(C);
            }

            virtual ~InternalLog()
            {
                *this << "\n";
            }

            template<typename T, std::ostream &IC>
            friend InternalLog<IC> &operator<<(InternalLog<IC> &, const T &);

            // Additional overload to handle ostream specific IO manipulators
            template<std::ostream &IC>
            friend InternalLog<IC> &operator<<(InternalLog<IC> &,
                                               std::ostream &(*)(std::ostream &));

            std::ostream &get_ostream()
            {
                return *this;
            }

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

            void print_header(std::ostream &out)
            {
                out << "[" << char_from_level(m_level) << "] "
                    << m_location.m_file << ":"
                    << m_location.m_line << "("
                    << m_location.m_function << ") ";
            }

        private:
            log_level m_level;
            log_location m_location;
    };

    template<typename T, std::ostream &C>
    inline InternalLog<C> &operator<<(InternalLog<C> &out, const T &value)
    {
        static_cast<std::ostream &>(out) << value;
        return out;
    }

    template<std::ostream &C>
    inline InternalLog<C> &operator<<(InternalLog<C> &out,
                                      std::ostream &(*f)(std::ostream &))
    {
        static_cast<std::ostream &>(out) << f;
        return out;
    }
};


#define FLOG() logger::InternalLog<std::cerr>(logger::log_level::fatal, \
                                              logger::log_location(__func__, \
                                                                   __FILE__, \
                                                                   __LINE__))
#define ALOG() logger::InternalLog<std::cerr>(logger::log_level::alert, \
                                              logger::log_location(__func__, \
                                                                   __FILE__, \
                                                                   __LINE__))
#define CLOG() logger::InternalLog<std::cerr>(logger::log_level::crit, \
                                              logger::log_location(__func__, \
                                                                   __FILE__, \
                                                                   __LINE__))
#define ELOG() logger::InternalLog<std::cerr>(logger::log_level::error, \
                                              logger::log_location(__func__, \
                                                                   __FILE__, \
                                                                   __LINE__))
#define WLOG() logger::InternalLog<std::cerr>(logger::log_level::warn, \
                                              logger::log_location(__func__, \
                                                                   __FILE__, \
                                                                   __LINE__))
#define NLOG() logger::InternalLog<std::cerr>(logger::log_level::notice, \
                                              logger::log_location(__func__, \
                                                                   __FILE__, \
                                                                   __LINE__))
#define ILOG() logger::InternalLog<std::cerr>(logger::log_level::info, \
                                              logger::log_location(__func__, \
                                                                   __FILE__, \
                                                                   __LINE__))
#define DLOG() logger::InternalLog<std::cerr>(logger::log_level::debug, \
                                              logger::log_location(__func__, \
                                                                   __FILE__, \
                                                                   __LINE__))
#define TLOG() logger::InternalLog<std::cerr>(logger::log_level::trace, \
                                              logger::log_location(__func__, \
                                                                   __FILE__, \
                                                                   __LINE__))

#endif /* end of include guard: LOGGER_H_SOWJCIS8 */
