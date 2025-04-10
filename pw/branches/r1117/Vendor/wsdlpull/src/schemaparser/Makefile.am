## This is the input file for automake, which will generate Makefile.in ##

MAINTAINERCLEANFILES = Makefile.in

# src/schemaparser
include $(srcdir)/sources.mk

#
lib_LTLIBRARIES = libwsdlpullschema.la

libwsdlpullschema_la_SOURCES = $(schema_h_sources) $(schema_cc_sources)
libwsdlpullschema_la_CPPFLAGS = -DSCHEMADIR=\"$(datadir)/wsdlpull/\"
libwsdlpullschema_la_LDFLAGS = $(top_builddir)/src/xmlpull/libwsdlpullxml.la \
	-version-info $(GENERIC_LIBRARY_VERSION)

#
pkginclude_HEADERS = $(schema_h_sources)
pkgincludedir= $(includedir)/wsdlpull/schemaparser

