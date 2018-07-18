/**
* @file logger.h
* @brief Define helper class to print log on stderr, mainly for debug purpose.
* @author Adrien Oliva
* @date 2017-10-10
*/
#ifndef LOGGER_H_SOWJCIS8
#define LOGGER_H_SOWJCIS8

#ifdef HAVE_YAPLOG
#include <yaplog.h>
#else
#include <ostream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <fstream>

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

                offset.str("");
                offset << "\n";
                offset << std::setw(8) << std::setfill('0')
                       << std::hex << (i);
                offset << " ";
                hexa.str("");
                ascii.str("");
                for (i = 0; i < m_size; i++) {
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

                        offset.str("");
                        offset << "\n";
                        offset << std::setw(8) << std::setfill('0')
                               << std::hex << (i + 1);
                        offset << " ";
                        hexa.str("");
                        ascii.str("");
                    }
                }

                if (i % 16 != 0) {
                    output << offset.str();
                    output << std::setw(49) << std::setfill(' ') << std::left << hexa.str();
                    output << "|";
                    output << std::setw(17) << std::setfill(' ') << std::left << ascii.str();
                    output << "|";
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
        none = 0,
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
    class InternalLog
    {
        public:
            /**
            * @brief Contructor of a simple logger, linked to any standard
            *        output stream.
            *
            * @param level The log level of the given logger.
            * @param loc Information of location of log in code base.
            * @param destination Standard output stream to be used.
            * @param system_level System log level.
            */
            InternalLog(log_level level, const log_location &loc,
                        std::ostream *destination,
                        log_level system_level = log_level::trace)
                : m_level(level)
                , m_location(loc)
                , m_output(destination)
                , m_systemlevel(system_level)
            {
                if (m_level <= m_systemlevel)
                    print_header();
            }

            virtual ~InternalLog()
            {
                if (m_level <= m_systemlevel) {
                    (*this) << "\n";
                }
                closeOstream(m_output);
            }

            template<typename T>
            friend const InternalLog &operator<<(const InternalLog &, const T &);

            template<typename T>
            friend const InternalLog &operator<<(const InternalLog &out, const T *value);
            /**
            * @brief Additional overload to handle ostream specific IO
            *         manipulators
            *
            * @param out Internal logger where IO manipulators must aplly.
            * @param f IO function manipulators.
            *
            * @return Internal logger instance.
            */
            friend const InternalLog &operator<<(const InternalLog &out,
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
                (*m_output) << "[" << char_from_level(m_level) << "] "
                            << m_location.m_file << ":"
                            << m_location.m_line << "("
                            << m_location.m_function << ") ";
            }

        public:
            /**
            * @brief Get configured output stream where log are put.
            *
            * @return Output stream to be used by logger, depending on
            *         `CSER_LOGDESTINATION` environment variable.
            *
            * If no environment variable is set, default is std::cerr.
            * When `CSER_LOGDESTINATION` is set to `stdout` or `stderr`, stream
            * is respectively redirected to std::cout or std::cerr, otherwise,
            * logger considers variable content as a filename and try to open
            * it in append mode. If file does not exists, logger create file.
            * Upon failure, logger falls back to std::cerr.
            */
            static std::ostream *getOstream()
            {
                const char *cser_logdestination = std::getenv("CSER_LOGDESTINATION");
                if (cser_logdestination == NULL) {
                    return new std::ostream(std::cerr.rdbuf());
                } else {
                    if (strcmp(cser_logdestination, "stderr") == 0) {
                        return new std::ostream(std::cerr.rdbuf());
                    } else if (strcmp(cser_logdestination, "stdout") == 0) {
                        return new std::ostream(std::cout.rdbuf());
                    } else {
                        return new std::ofstream(cser_logdestination,
                                                 std::ofstream::app);
                    }
                }
                return new std::ostream(std::cerr.rdbuf());
            }

            /**
            * @brief Close the given output stream properly.
            *
            * @param os Output stream to close.
            */
            static void closeOstream(std::ostream *os)
            {
                delete os;
            }

            /**
            * @brief Get configured logger level to show.
            *
            * @return Log level used by logger, depending on `CSER_LOGLEVEL`
            *         environment variable.
            *
            * When `CSER_LOGLEVEL` is set to any number between 0 and 9, logger
            * directly use the log level and print to output every log message
            * with level lower or equal to the given system log level.
            * If `CSER_LOGLEVEL` is set to a number lower than 0, 0 is used.
            * If `CSER_LOGLEVEL` is set to a number higher than 9, 9 is used.
            * If `CSER_LOGLEVEL` is not set to a number, 0 is used.
            * If no environment variable is set, default is 0.
            */
            static log_level getSystemLevel()
            {
                const char *cser_loglevel = std::getenv("CSER_LOGLEVEL");
                if (cser_loglevel == NULL) {
                    return log_level::none;
                } else {
                    try {
                        int value = std::stoi(cser_loglevel);
                        if (value < 0)
                            return log_level::none;
                        if (value > 9)
                            return log_level::trace;
                        return static_cast<log_level>(value);
                    } catch (std::exception &) {
                        return log_level::none;
                    }
                }
            }

        protected:
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
            std::ostream *m_output;
            /**
            * @brief System log level.
            */
            log_level m_systemlevel;
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
    inline const InternalLog &operator<<(const InternalLog &out, const T &value)
    {
        if (out.m_level <= out.m_systemlevel)
            (*out.m_output) << value;
        return out;
    }
    /**
    * @brief Print any type to an internal logger instance.
    *
    * @tparam T Typename of data to print
    * @param out Internal logger instance where data will be printed
    * @param value Pointer to data to print
    *
    * @return Internal logger instance used.
    */
    template<typename T>
    inline const InternalLog &operator<<(const InternalLog &out, const T *value)
    {
        if (out.m_level <= out.m_systemlevel)
            (*out.m_output) << value;
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
    inline const InternalLog &operator<<(const InternalLog &out,
                                         std::ostream &(*f)(std::ostream &))
    {
        if (out.m_level <= out.m_systemlevel)
            (*out.m_output) << f;
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
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())

/**
 * @brief Alert log macro utility to print an alert message on stderr.
 */
#define ALOG() logger::InternalLog(logger::log_level::alert, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())
/**
 * @brief Critical log macro utility to print a critical message on stderr.
 */
#define CLOG() logger::InternalLog(logger::log_level::crit, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())
/**
 * @brief Error log macro utility to print an error message on stderr.
 */
#define ELOG() logger::InternalLog(logger::log_level::error, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())
/**
 * @brief Warning log macro utility to print a warning message on stderr.
 */
#define WLOG() logger::InternalLog(logger::log_level::warn, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())
/**
 * @brief Notice log macro utility to print a notice message on stderr.
 */
#define NLOG() logger::InternalLog(logger::log_level::notice, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())
/**
 * @brief Information log macro utility to print an information message on
 *        stderr.
 */
#define ILOG() logger::InternalLog(logger::log_level::info, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())
/**
 * @brief Debug log macro utility to print a debug message on stderr.
 */
#define DLOG() logger::InternalLog(logger::log_level::debug, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())
/**
 * @brief Trace log macro utility to print a trace message on stderr.
 */
#define TLOG() logger::InternalLog(logger::log_level::trace, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())

#endif
#endif /* end of include guard: LOGGER_H_SOWJCIS8 */
