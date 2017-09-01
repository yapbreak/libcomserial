#ifndef UT_EXCEPTIONS_H_BZJ0KWTM
#define UT_EXCEPTIONS_H_BZJ0KWTM

#include <comserial.h>

#include <CppUTest/TestHarness.h>
#include "fixtures.h"

TEST_GROUP(cppinterface_exception)
{
};

TEST(cppinterface_exception, device_not_found)
{
    check_exception<com::exception::device_not_found>("Device not found");
}

#endif /* end of include guard: UT_EXCEPTIONS_H_BZJ0KWTM */
