#ifndef UT_CMODULE_H_UJEVLXFG
#define UT_CMODULE_H_UJEVLXFG

#include <serialcomm/cserialcomm.h>

#include <CppUTest/TestHarness.h>

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
    serialcomm_t s;

    s = serialcomm_create_device("unavailable");
    POINTERS_EQUAL(NULL, s);
}

TEST(cinterface_module, close_non_existing)
{
    serialcomm_destroy_device(NULL);
}

#endif /* end of include guard: UT_CMODULE_H_UJEVLXFG */
