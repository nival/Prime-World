## This is the input file for automake, which will generate Makefile.in ##
# src/schemaparser
include $(srcdir)/sources.mk

MAINTAINERCLEANFILES = Makefile.in

# Libraries to be exported
lib_LTLIBRARIES = libwsdlpull.la

#
libwsdlpull_la_SOURCES = $(wsdl_h_sources) $(wsdl_cc_sources)
libwsdlpull_la_CPPFLAGS = -DSCHEMADIR=\"$(datadir)/wsdlpull/\"
libwsdlpull_la_LDFLAGS = $(top_builddir)/src/xmlpull/libwsdlpullxml.la \
	$(top_builddir)/src/schemaparser/libwsdlpullschema.la \
	-version-info $(GENERIC_LIBRARY_VERSION)

# Header files to be exported
pkginclude_HEADERS = $(schema_h_sources)
pkgincludedir= $(includedir)/wsdlpull/wsdlparser
