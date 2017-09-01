#ifndef UT_CPPMODULE_H_OWBGUT0J
#define UT_CPPMODULE_H_OWBGUT0J

#include <comserial/cppcomserial.h>

#include <CppUTest/TestHarness.h>
#include <string>

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
}


#endif /* end of include guard: UT_CPPMODULE_H_OWBGUT0J */
