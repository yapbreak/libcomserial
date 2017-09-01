#ifndef UT_LOG_LOCATION_H_QL3WBUGD
#define UT_LOG_LOCATION_H_QL3WBUGD

#include "logger.h"
#include "utils.h"

#include <cstring>

#include <CppUTest/TestHarness.h>

using namespace logger;

TEST_GROUP(loglocation)
{
};

TEST(loglocation, creation)
{
    log_location l("function", "file", 42);

    STRCMP_EQUAL("function", l.m_function.c_str());
    STRCMP_EQUAL("file", l.m_file.c_str());
    UNSIGNED_LONGS_EQUAL(42, l.m_line);
}

#endif /* end of include guard: UT_LOG_LOCATION_H_QL3WBUGD */
