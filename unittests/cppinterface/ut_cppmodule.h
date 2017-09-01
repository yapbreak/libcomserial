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


#endif /* end of include guard: UT_CPPMODULE_H_OWBGUT0J */
