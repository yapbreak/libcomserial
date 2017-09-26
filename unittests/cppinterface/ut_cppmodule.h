#ifndef UT_CPPMODULE_H_OWBGUT0J
#define UT_CPPMODULE_H_OWBGUT0J

#include <comserial/cppcomserial.h>

#include <CppUTest/TestHarness.h>
#include <string>

#include "logger.h"

TEST_GROUP(cppinterface_module)
{
    fake::serial *m_serial;
    std::string com_in = "com_in";
    std::string com_out = "com_out";

    void setup()
    {
        m_serial = new fake::serial(com_in, com_out);
    };

    void teardown()
    {
        delete m_serial;
    };

};

TEST(cppinterface_module, open_non_existing)
{
    com::serial *serial = NULL;

    CHECK_THROWS(com::exception::device_not_found,
                 serial = new com::serial("unavailable"));

    delete serial;
};

SOCAT_TEST(cppinterface_module, open_existing)
{
    try {
        com::serial serial("com_in");
    } catch (std::exception &e) {
        ELOG() << e.what();
        FAIL("Exception thrown");
    }
};

SOCAT_TEST(cppinterface_module, check_default_speed)
{
    com::serial serial("com_in");

    UNSIGNED_LONGS_EQUAL(19200, serial.get_speed());
}

SOCAT_TEST(cppinterface_module, check_user_defined_valid_speed)
{
    com::serial serial("com_in", 9600);

    UNSIGNED_LONGS_EQUAL(9600, serial.get_speed());
}

SOCAT_TEST(cppinterface_module, set_valid_speed_after)
{
    com::serial serial("com_in");

    unsigned int old_speed = serial.set_speed(115200);
    UNSIGNED_LONGS_EQUAL(19200, old_speed);
    UNSIGNED_LONGS_EQUAL(115200, serial.get_speed());
}

SOCAT_TEST(cppinterface_module, create_invalid_speed)
{
    com::serial *serial = NULL;

    CHECK_THROWS(com::exception::invalid_speed,
                 serial = new com::serial("com_in", 1234));

    delete serial;
}

SOCAT_TEST(cppinterface_module, set_invalid_speed)
{
    com::serial serial("com_in");

    CHECK_THROWS(com::exception::invalid_speed,
                 serial.set_speed(4321));
}

SOCAT_TEST(cppinterface_module, set_all_valid_speed)
{
    com::serial serial("com_in");

    unsigned int valid_speed[] = {
        19200,
        50,
        75,
        110,
        134,
        150,
        200,
        300,
        600,
        1200,
        1800,
        2400,
        4800,
        9600,
        19200,
        38400,
        57600,
        115200,
        230400
    };

    for (size_t i = 1; i < DIM_OF(valid_speed); i++)
        UNSIGNED_LONGS_EQUAL(valid_speed[i - 1],
                             serial.set_speed(valid_speed[i]));
}

SOCAT_TEST(cppinterface_module, check_default_data_size)
{
    com::serial serial("com_in");

    UNSIGNED_LONGS_EQUAL(8, serial.get_data_size());
}

SOCAT_TEST(cppinterface_module, check_user_defined_valid_data_size)
{
    com::serial serial("com_in", 19200, 7);

    UNSIGNED_LONGS_EQUAL(7, serial.get_data_size());
}

SOCAT_TEST(cppinterface_module, set_valid_data_size_after)
{
    com::serial serial("com_in");

    unsigned int old_data_size = serial.set_data_size(7);
    UNSIGNED_LONGS_EQUAL(8, old_data_size);
    UNSIGNED_LONGS_EQUAL(7, serial.get_data_size());
}

SOCAT_TEST(cppinterface_module, create_invalid_data_size)
{
    com::serial *serial = NULL;

    CHECK_THROWS(com::exception::invalid_data_size,
                 serial = new com::serial("com_in", 19200, 1234));

    delete serial;
}

SOCAT_TEST(cppinterface_module, set_invalid_data_size)
{
    com::serial serial("com_in");

    CHECK_THROWS(com::exception::invalid_data_size,
                 serial.set_data_size(4321));
}

SOCAT_TEST(cppinterface_module, set_all_valid_data_size)
{
    com::serial serial("com_in");

    unsigned int valid_data_size[] = {
        8, 5, 6, 7, 8
    };

    for (size_t i = 1; i < DIM_OF(valid_data_size); i++)
        UNSIGNED_LONGS_EQUAL(valid_data_size[i - 1],
                             serial.set_data_size(valid_data_size[i]));
}

#endif /* end of include guard: UT_CPPMODULE_H_OWBGUT0J */
