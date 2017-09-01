ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/Makefile.common

lib_LTLIBRARIES = libserialcomm.la
libserialcomm_la_SOURCES  = serialcomm.h
libserialcomm_la_SOURCES += serialcomm/cserialcomm.h
libserialcomm_la_SOURCES += serialcomm/cppserialcomm.h
libserialcomm_la_SOURCES += cserialcomm.cpp
libserialcomm_la_SOURCES += cppserialcomm.cpp
libserialcomm_la_SOURCES += __init__.cpp

subdirheadersdir = $(includedir)/serialcomm
subdirheaders_HEADERS  = serialcomm.h
subdirheaders_HEADERS += serialcomm/cserialcomm.h
subdirheaders_HEADERS += serialcomm/cppserialcomm.h
