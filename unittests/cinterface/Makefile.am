ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/unittests/Makefile.test.common

TESTS = ut_cinterface.xtest

if INSTALLTEST
bin_PROGRAMS = $(TESTS)
else
noinst_PROGRAMS = $(TESTS)
endif

check_PROGRAMS = $(TESTS)

ut_cinterface_xtest_SOURCES  = ut_cmodule.h
ut_cinterface_xtest_SOURCES += ut_cinterface.cpp
ut_cinterface_xtest_CFLAGS = $(TESTCFLAGS)
ut_cinterface_xtest_CXXFLAGS = $(TESTCXXFLAGS)
ut_cinterface_xtest_LDFLAGS = $(TESTLDFLAGS)
ut_cinterface_xtest_LDADD  = $(top_builddir)/unittests/fixtures/libfixtures.la
ut_cinterface_xtest_LDADD += $(top_builddir)/src/libcomserial.la
