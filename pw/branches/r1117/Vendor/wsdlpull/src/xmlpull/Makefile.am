## This is the input file for automake, which will generate Makefile.in ##

MAINTAINERCLEANFILES = Makefile.in

# src/xmlpull
include $(srcdir)/sources.mk

INCLUDES = -I$(top_builddir) -I$(top_builddir)/src  -I.

lib_LTLIBRARIES = libwsdlpullxml.la

libwsdlpullxml_la_SOURCES = $(xmlpull_h_sources) $(xmlpull_cc_sources)
libwsdlpullxml_la_LDFLAGS = -lpthread -version-info $(GENERIC_LIBRARY_VERSION)

pkginclude_HEADERS = $(xmlpull_h_sources)
pkgincludedir= $(includedir)/wsdlpull/xml

