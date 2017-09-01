#ifndef UT_INTERNALLOG_H_NKWOOHP7
#define UT_INTERNALLOG_H_NKWOOHP7

#include "logger.h"
#include "utils.h"

#include <CppUTest/TestHarness.h>
#include <sstream>

using namespace logger;


TEST_GROUP(internallog)
{
    void setup()
    {
        std::ostringstream my_real_stream = std::ostringstream();
    };

    void teardown()
    {
    };

    std::ostringstream my_real_stream;
};

TEST(internallog, nodata)
{
    InternalLog(log_level::fatal,
                log_location("function", "file", 42),
                my_real_stream);

    STRCMP_EQUAL("[F] file:42(function) \n",
                 my_real_stream.str().c_str());
};

TEST(internallog, dynamicallocation)
{
    InternalLog *log = new InternalLog(log_level::alert,
                                       log_location("function2", "file2", 38),
                                       my_real_stream);

    delete log;

    STRCMP_EQUAL("[A] file2:38(function2) \n",
                 my_real_stream.str().c_str());
};

#endif /* end of include guard: UT_INTERNALLOG_H_NKWOOHP7 */
