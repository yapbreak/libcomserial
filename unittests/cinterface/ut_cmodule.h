#ifndef UT_CMODULE_H_UJEVLXFG
#define UT_CMODULE_H_UJEVLXFG

#include <comserial/ccomserial.h>

#include <CppUTest/TestHarness.h>
#include <string>

TEST_GROUP(cinterface_module)
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

TEST(cinterface_module, open_non_existing)
{
    comserial_t s;

    s = comserial_create_device("unavailable");
    POINTERS_EQUAL(NULL, s);
}

TEST(cinterface_module, open_existing_notty)
{
    comserial_t s;

    s = comserial_create_device("/dev/null");
    POINTERS_EQUAL(NULL, s);
}

TEST(cinterface_module, close_non_existing)
{
    comserial_destroy_device(NULL);
}

SOCAT_TEST(cinterface_module, open_existing)
{
    comserial_t s;

    s = comserial_create_device("com_in");
    CHECK(NULL != s);

    comserial_destroy_device(&s);
    POINTERS_EQUAL(NULL, s);
}

TEST(cinterface_module, get_speed_invalid_device)
{
    UNSIGNED_LONGS_EQUAL(0, comserial_get_speed(NULL));
}

TEST(cinterface_module, set_speed_invalid_device)
{
    UNSIGNED_LONGS_EQUAL(0, comserial_set_speed(NULL, 115200));
}

TEST(cinterface_module, get_data_size_invalid_device)
{
    UNSIGNED_LONGS_EQUAL(0, comserial_get_data_size(NULL));
}

TEST(cinterface_module, set_data_size_invalid_device)
{
    UNSIGNED_LONGS_EQUAL(0, comserial_set_data_size(NULL, 8));
}

TEST(cinterface_module, get_stop_size_invalid_device)
{
    UNSIGNED_LONGS_EQUAL(0, comserial_get_stop_size(NULL));
}

TEST(cinterface_module, set_stop_size_invalid_device)
{
    UNSIGNED_LONGS_EQUAL(0, comserial_set_stop_size(NULL, 2));
}

TEST(cinterface_module, get_parity_invalid_device)
{
    UNSIGNED_LONGS_EQUAL(0, comserial_get_parity(NULL));
}

TEST(cinterface_module, set_parity_invalid_device)
{
    UNSIGNED_LONGS_EQUAL(0, comserial_set_parity(NULL, 'o'));
}

TEST(cinterface_module, get_read_timeout_invalid_device)
{
    UNSIGNED_LONGS_EQUAL(0, comserial_get_read_timeout(NULL));
}

TEST(cinterface_module, set_read_timeout_invalid_device)
{
    UNSIGNED_LONGS_EQUAL(0, comserial_set_read_timeout(NULL, 10));
}

TEST(cinterface_module, get_write_timeout_invalid_device)
{
    UNSIGNED_LONGS_EQUAL(0, comserial_get_write_timeout(NULL));
}

TEST(cinterface_module, set_write_timeout_invalid_device)
{
    UNSIGNED_LONGS_EQUAL(0, comserial_set_write_timeout(NULL, 10));
}

TEST_GROUP(cinterface_valid_module)
{
    fake::serial *m_serial;
    std::string com_in = "com_in";
    std::string com_out = "com_out";
    comserial_t m_comserial;

    void setup()
    {
        m_serial = new fake::serial(com_in, com_out);
        m_comserial = comserial_create_device("com_in");
    };

    void teardown()
    {
        comserial_destroy_device(&m_comserial);
        delete m_serial;
    };
};

SOCAT_TEST(cinterface_valid_module, check_default_speed)
{
    UNSIGNED_LONGS_EQUAL(19200, comserial_get_speed(m_comserial));
}

SOCAT_TEST(cinterface_valid_module, set_valid_speed)
{
    unsigned int old_speed = comserial_set_speed(m_comserial, 115200);
    UNSIGNED_LONGS_EQUAL(19200, old_speed);
    UNSIGNED_LONGS_EQUAL(115200, comserial_get_speed(m_comserial));
}

SOCAT_TEST(cinterface_valid_module, set_invalid_speed)
{
    UNSIGNED_LONGS_EQUAL(0, comserial_set_speed(m_comserial, 1234));
}

SOCAT_TEST(cinterface_valid_module, check_default_data_size)
{
    UNSIGNED_LONGS_EQUAL(8, comserial_get_data_size(m_comserial));
}

SOCAT_TEST(cinterface_valid_module, set_valid_data_size)
{
    unsigned int old_data_size = comserial_set_data_size(m_comserial, 7);
    UNSIGNED_LONGS_EQUAL(8, old_data_size);
    UNSIGNED_LONGS_EQUAL(7, comserial_get_data_size(m_comserial));
}

SOCAT_TEST(cinterface_valid_module, set_invalid_data_size)
{
    UNSIGNED_LONGS_EQUAL(0, comserial_set_data_size(m_comserial, 1234));
}

SOCAT_TEST(cinterface_valid_module, check_default_stop_size)
{
    UNSIGNED_LONGS_EQUAL(1, comserial_get_stop_size(m_comserial));
}

SOCAT_TEST(cinterface_valid_module, set_valid_stop_size)
{
    unsigned int old_stop_size = comserial_set_stop_size(m_comserial, 2);
    UNSIGNED_LONGS_EQUAL(1, old_stop_size);
    UNSIGNED_LONGS_EQUAL(2, comserial_get_stop_size(m_comserial));
}

SOCAT_TEST(cinterface_valid_module, set_invalid_stop_size)
{
    UNSIGNED_LONGS_EQUAL(0, comserial_set_stop_size(m_comserial, 1234));
}

SOCAT_TEST(cinterface_valid_module, check_default_parity)
{
    UNSIGNED_LONGS_EQUAL('n', comserial_get_parity(m_comserial));
}

SOCAT_TEST(cinterface_valid_module, set_valid_parity)
{
    char old_parity = comserial_set_parity(m_comserial, 'E');
    UNSIGNED_LONGS_EQUAL('n', old_parity);
    UNSIGNED_LONGS_EQUAL('e', comserial_get_parity(m_comserial));
}

SOCAT_TEST(cinterface_valid_module, set_invalid_parity)
{
    UNSIGNED_LONGS_EQUAL(0, comserial_set_parity(m_comserial, 'P'));
}

SOCAT_TEST(cinterface_valid_module, check_default_read_timeout)
{
    UNSIGNED_LONGS_EQUAL(1000, comserial_get_read_timeout(m_comserial));
}

SOCAT_TEST(cinterface_valid_module, set_valid_read_timeout)
{
    unsigned long old_read_timeout = comserial_set_read_timeout(m_comserial, 15);
    UNSIGNED_LONGS_EQUAL(1000, old_read_timeout);
    UNSIGNED_LONGS_EQUAL(15, comserial_get_read_timeout(m_comserial));
}

SOCAT_TEST(cinterface_valid_module, check_default_write_timeout)
{
    UNSIGNED_LONGS_EQUAL(1000, comserial_get_write_timeout(m_comserial));
}

SOCAT_TEST(cinterface_valid_module, set_valid_write_timeout)
{
    unsigned long old_write_timeout = comserial_set_write_timeout(m_comserial, 15);
    UNSIGNED_LONGS_EQUAL(1000, old_write_timeout);
    UNSIGNED_LONGS_EQUAL(15, comserial_get_write_timeout(m_comserial));
}

#endif /* end of include guard: UT_CMODULE_H_UJEVLXFG */
