ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/unittests/Makefile.test.common

TESTS = ut_logger.xtest

if INSTALLTEST
bin_PROGRAMS = $(TESTS)
else
noinst_PROGRAMS = $(TESTS)
endif

check_PROGRAMS = $(TESTS)

ut_logger_xtest_SOURCES  = ut_dumper.h
ut_logger_xtest_SOURCES += ut_logger.cpp
ut_logger_xtest_CFLAGS = $(TESTCFLAGS)
ut_logger_xtest_CXXFLAGS = $(TESTCXXFLAGS)
ut_logger_xtest_LDFLAGS = $(TESTLDFLAGS)
ut_logger_xtest_LDADD  = $(top_builddir)/unittests/fixtures/libfixtures.la
ut_logger_xtest_LDADD += $(top_builddir)/src/libcomserial.la
