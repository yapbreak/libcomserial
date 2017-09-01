#ifndef EXCEPTIONS_H_OZFRKXV6
#define EXCEPTIONS_H_OZFRKXV6

#include <exception>

namespace com
{

    namespace exception
    {

        class device_not_found : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return "Device not found";
                };
        };

    };

};

#endif /* end of include guard: EXCEPTIONS_H_OZFRKXV6 */
