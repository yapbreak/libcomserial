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

TEST(cppinterface_exception, invalid_speed)
{
    com::exception::invalid_speed *pe = new com::exception::invalid_speed(42);
    STRCMP_EQUAL("Invalid speed (42)", pe->what());
    delete pe;

    pe = new com::exception::invalid_speed(1234);
    STRCMP_EQUAL("Invalid speed (1234)", pe->what());
    delete pe;
};

TEST(cppinterface_exception, invalid_configuration)
{
    check_exception<com::exception::invalid_configuration>(
                                                "Invalid configuration set");
}

TEST(cppinterface_exception, invalid_data_size)
{
    com::exception::invalid_data_size *pe =
                                    new com::exception::invalid_data_size(42);
    STRCMP_EQUAL("Invalid data size (42)", pe->what());
    delete pe;

    pe = new com::exception::invalid_data_size(1234);
    STRCMP_EQUAL("Invalid data size (1234)", pe->what());
    delete pe;
};


#endif /* end of include guard: UT_EXCEPTIONS_H_BZJ0KWTM */
