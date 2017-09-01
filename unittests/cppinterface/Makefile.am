ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/unittests/Makefile.test.common

TESTS = ut_cppinterface.xtest

if INSTALLTEST
bin_PROGRAMS = $(TESTS)
else
noinst_PROGRAMS = $(TESTS)
endif

check_PROGRAMS = $(TESTS)

ut_cppinterface_xtest_SOURCES  = ut_cppmodule.h
ut_cppinterface_xtest_SOURCES += ut_cppinterface.cpp
ut_cppinterface_xtest_CFLAGS = $(TESTCFLAGS)
ut_cppinterface_xtest_CXXFLAGS = $(TESTCXXFLAGS)
ut_cppinterface_xtest_LDFLAGS = $(TESTLDFLAGS)
ut_cppinterface_xtest_LDADD  = $(top_builddir)/unittests/fixtures/libfixtures.la
ut_cppinterface_xtest_LDADD += $(top_builddir)/src/libcomserial.la


