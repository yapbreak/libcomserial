ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/Makefile.common

SUBDIRS =  comserial

lib_LTLIBRARIES = libcomserial.la
libcomserial_la_SOURCES  = comserial.h
libcomserial_la_SOURCES += ccomserial.cpp
libcomserial_la_SOURCES += cppcomserial.cpp
libcomserial_la_SOURCES += __init__.cpp

include_HEADERS = comserial.h
