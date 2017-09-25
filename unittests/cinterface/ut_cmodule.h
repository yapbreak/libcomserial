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

#endif /* end of include guard: UT_CMODULE_H_UJEVLXFG */
