ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/unittests/Makefile.test.common

noinst_LTLIBRARIES = libfixtures.la
libfixtures_la_SOURCES  = utils.h
libfixtures_la_SOURCES += exception.h
libfixtures_la_SOURCES += fixtures.h
libfixtures_la_SOURCES += fakeserial.h
libfixtures_la_SOURCES += fakeserial.cpp
libfixtures_la_CFLAGS = $(TESTCFLAGS)
libfixtures_la_CXXFLAGS = $(TESTCXXFLAGS)
libfixtures_la_LDFLAGS = $(TESTLDFLAGS)
libfixtures_la_LIBADD = $(top_builddir)/src/libserialcomm.la
