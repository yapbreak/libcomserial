#ifndef UT_CPPMODULE_H_OWBGUT0J
#define UT_CPPMODULE_H_OWBGUT0J

#include <comserial/cppcomserial.h>

#include <CppUTest/TestHarness.h>
#include <string>
#include <cstring>

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

TEST(cppinterface_module, open_existing_notty)
{
    com::serial *serial = NULL;

    CHECK_THROWS(com::exception::invalid_device,
                 serial = new com::serial("/dev/null"));

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

SOCAT_TEST(cppinterface_module, check_default_stop_size)
{
    com::serial serial("com_in");

    UNSIGNED_LONGS_EQUAL(1, serial.get_stop_size());
}

SOCAT_TEST(cppinterface_module, check_user_defined_valid_stop_size)
{
    com::serial serial("com_in", 19200, 8, 2);

    UNSIGNED_LONGS_EQUAL(2, serial.get_stop_size());
}

SOCAT_TEST(cppinterface_module, set_valid_stop_size_after)
{
    com::serial serial("com_in");

    unsigned int old_stop_size = serial.set_stop_size(2);
    UNSIGNED_LONGS_EQUAL(1, old_stop_size);
    UNSIGNED_LONGS_EQUAL(2, serial.get_stop_size());
}

SOCAT_TEST(cppinterface_module, create_invalid_stop_size)
{
    com::serial *serial = NULL;

    CHECK_THROWS(com::exception::invalid_stop_size,
                 serial = new com::serial("com_in", 19200, 8, 4));

    delete serial;
}

SOCAT_TEST(cppinterface_module, set_invalid_stop_size)
{
    com::serial serial("com_in");

    CHECK_THROWS(com::exception::invalid_stop_size,
                 serial.set_stop_size(4321));
}

SOCAT_TEST(cppinterface_module, set_all_valid_stop_size)
{
    com::serial serial("com_in");

    unsigned int valid_stop_size[] = {
        1, 1, 2
    };

    for (size_t i = 1; i < DIM_OF(valid_stop_size); i++)
        UNSIGNED_LONGS_EQUAL(valid_stop_size[i - 1],
                             serial.set_stop_size(valid_stop_size[i]));
}

SOCAT_TEST(cppinterface_module, check_default_parity)
{
    com::serial serial("com_in");

    UNSIGNED_LONGS_EQUAL('n', serial.get_parity());
}

SOCAT_TEST(cppinterface_module, check_user_defined_valid_parity)
{
    com::serial serial("com_in", 19200, 8, 2, 'o');

    UNSIGNED_LONGS_EQUAL('o', serial.get_parity());
}

SOCAT_TEST(cppinterface_module, set_valid_parity_after)
{
    com::serial serial("com_in");

    char old_parity = serial.set_parity('O');
    UNSIGNED_LONGS_EQUAL('n', old_parity);
    UNSIGNED_LONGS_EQUAL('o', serial.get_parity());
}

SOCAT_TEST(cppinterface_module, create_invalid_parity)
{
    com::serial *serial = NULL;

    CHECK_THROWS(com::exception::invalid_parity,
                 serial = new com::serial("com_in", 19200, 8, 1, 'X'));

    delete serial;
}

SOCAT_TEST(cppinterface_module, set_invalid_parity)
{
    com::serial serial("com_in");

    CHECK_THROWS(com::exception::invalid_parity,
                 serial.set_parity('X'));
}

SOCAT_TEST(cppinterface_module, set_all_valid_parity)
{
    com::serial serial("com_in");

    char valid_parity[] = {
        'n', 'o', 'e', 'n'
    };

    for (size_t i = 1; i < DIM_OF(valid_parity); i++)
        UNSIGNED_LONGS_EQUAL(valid_parity[i - 1],
                             serial.set_parity(valid_parity[i]));
}

SOCAT_TEST(cppinterface_module, check_default_read_timeout)
{
    com::serial serial("com_in");

    UNSIGNED_LONGS_EQUAL(1000, serial.get_read_timeout());
}

SOCAT_TEST(cppinterface_module, check_default_write_timeout)
{
    com::serial serial("com_in");

    UNSIGNED_LONGS_EQUAL(1000, serial.get_write_timeout());
}

SOCAT_TEST(cppinterface_module, set_read_timeout)
{
    com::serial serial("com_in");
    unsigned int old_timeout = serial.set_read_timeout(10);

    UNSIGNED_LONGS_EQUAL(1000, old_timeout);
    UNSIGNED_LONGS_EQUAL(10, serial.get_read_timeout());
}

SOCAT_TEST(cppinterface_module, set_write_timeout)
{
    com::serial serial("com_in");
    unsigned int old_timeout = serial.set_write_timeout(10);

    UNSIGNED_LONGS_EQUAL(1000, old_timeout);
    UNSIGNED_LONGS_EQUAL(10, serial.get_write_timeout());
}

TEST_GROUP(cppinterface_io)
{
    fake::serial *m_serial;
    std::string com_in = "com_in";
    std::string com_out = "com_out";

    com::serial *in;
    com::serial *out;

    void setup()
    {
        m_serial = new fake::serial(com_in, com_out);

        in = new com::serial(com_in);
        out = new com::serial(com_out);
    };

    void teardown()
    {
        delete out;
        delete in;

        delete m_serial;
    };
};

SOCAT_TEST(cppinterface_io, write_buffer)
{
    uint8_t buffer[16];
    for (size_t index = 0; index < 16; index++)
        buffer[index] = static_cast<uint8_t>(index);

    UNSIGNED_LONGS_EQUAL(16, in->write_buffer(buffer, 16));
}

SOCAT_TEST(cppinterface_io, write_error)
{
    uint8_t buffer[16];
    CHECK_THROWS(com::exception::invalid_input,
                 in->write_buffer(NULL, 16));
    CHECK_THROWS(com::exception::invalid_input,
                 in->write_buffer(buffer, 0));
}

SOCAT_TEST(cppinterface_io, read_buffer)
{
    uint8_t buffer[16];
    uint8_t read_buffer[18];
    memset(read_buffer, 0xfe, sizeof(read_buffer));

    for (size_t index = 0; index < 16; index++)
        buffer[index] = static_cast<uint8_t>(index);

    in->write_buffer(buffer, 16);

    size_t read_size = out->read_buffer(&read_buffer[1], 16);

    UNSIGNED_LONGS_EQUAL(16, read_size);
    BYTES_EQUAL(0xfe, read_buffer[0]);
    BYTES_EQUAL(0xfe, read_buffer[read_size + 1]);
    MEMCMP_EQUAL(buffer, &read_buffer[1], 16);
}

SOCAT_TEST(cppinterface_io, read_buffer_small)
{
    uint8_t buffer[8];
    uint8_t read_buffer[10];
    memset(read_buffer, 0xfe, sizeof(read_buffer));

    for (size_t index = 0; index < 8; index++)
        buffer[index] = static_cast<uint8_t>(rand());

    UNSIGNED_LONGS_EQUAL(8, in->write_buffer(buffer, 8));

    size_t read_size = out->read_buffer(&read_buffer[1], 8);

    UNSIGNED_LONGS_EQUAL(8, read_size);
    BYTES_EQUAL(0xfe, read_buffer[0]);
    BYTES_EQUAL(0xfe, read_buffer[read_size + 1]);
    MEMCMP_EQUAL(buffer, &read_buffer[1], 8);
}

SOCAT_TEST(cppinterface_io, read_error)
{
    uint8_t buffer[16];
    CHECK_THROWS(com::exception::invalid_input,
                 in->read_buffer(NULL, 16));
    CHECK_THROWS(com::exception::invalid_input,
                 in->read_buffer(buffer, 0));
}

SOCAT_TEST(cppinterface_io, read_timeout)
{
    uint8_t buffer[4] = { 0xde, 0xad, 0xbe, 0xef };
    uint8_t read_buffer[16] = { };

    CHECK_THROWS(com::exception::timeout,
                 in->read_buffer(read_buffer, 16));

    in->write_buffer(buffer, 4);
    try {
        out->read_buffer(read_buffer, 16);
        FAIL("No exception thrown");
    } catch (const com::exception::timeout &e) {
        UNSIGNED_LONGS_EQUAL(4, e.get_bytes());
    }
    MEMCMP_EQUAL(buffer, read_buffer, 4);
}

#endif /* end of include guard: UT_CPPMODULE_H_OWBGUT0J */
