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

TEST(cppinterface_exception, invalid_stop_size)
{
    com::exception::invalid_stop_size *pe =
                                    new com::exception::invalid_stop_size(42);
    STRCMP_EQUAL("Invalid stop size (42)", pe->what());
    delete pe;

    pe = new com::exception::invalid_stop_size(1234);
    STRCMP_EQUAL("Invalid stop size (1234)", pe->what());
    delete pe;
};

TEST(cppinterface_exception, invalid_parity)
{
    com::exception::invalid_parity *pe =
                                    new com::exception::invalid_parity('X');
    STRCMP_EQUAL("Invalid parity (X)", pe->what());
    delete pe;

    pe = new com::exception::invalid_parity('Y');
    STRCMP_EQUAL("Invalid parity (Y)", pe->what());
    delete pe;
};

TEST(cppinterface_exception, invalid_device)
{
    com::exception::invalid_device *pe =
                            new com::exception::invalid_device("/dev/null");
    STRCMP_EQUAL("Invalid device (/dev/null)", pe->what());
    delete pe;

    pe = new com::exception::invalid_device("/tmp/");
    STRCMP_EQUAL("Invalid device (/tmp/)", pe->what());
    delete pe;
};

TEST(cppinterface_exception, invalid_input)
{
    check_exception<com::exception::invalid_input>("Invalid argument");
}

TEST(cppinterface_exception, timeout)
{
    check_exception<com::exception::timeout>("Timeout reached");

    com::exception::timeout t1(42);
    UNSIGNED_LONGS_EQUAL(42, t1.get_bytes());

    com::exception::timeout t2(21);
    UNSIGNED_LONGS_EQUAL(21, t2.get_bytes());
}

TEST(cppinterface_exception, runtime_error)
{
    com::exception::runtime_error *pe =
                            new com::exception::runtime_error("my message");
    STRCMP_EQUAL("Runtime error: my message", pe->what());
    delete pe;

    pe = new com::exception::runtime_error("another reason");
    STRCMP_EQUAL("Runtime error: another reason", pe->what());
    delete pe;
};


#endif /* end of include guard: UT_EXCEPTIONS_H_BZJ0KWTM */
