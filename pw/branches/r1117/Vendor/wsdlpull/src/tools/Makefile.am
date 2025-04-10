## This is the input file for automake, which will generate Makefile.in ##
# src/xmlpull
include $(srcdir)/sources.mk

MAINTAINERCLEANFILES = Makefile.in

## WSDL Invocation stuff
bin_PROGRAMS = wsdlpull wsdlpull-schema

## Dynamic Web service invocation
wsdlpull_SOURCES = $(wsdltool_cc_sources)
wsdlpull_CPPFLAGS = -DSCHEMADIR=\"$(datadir)/wsdlpull/\"
wsdlpull_LDFLAGS = \
	$(top_builddir)/src/xmlpull/libwsdlpullxml.la \
	$(top_builddir)/src/schemaparser/libwsdlpullschema.la \
	$(top_builddir)/src/wsdlparser/libwsdlpull.la

## Schema validation tool
wsdlpull_schema_SOURCES = $(schematool_cc_sources)
wsdlpull_schema_CPPFLAGS = -DSCHEMADIR=\"$(datadir)/wsdlpull/\"
wsdlpull_schema_LDFLAGS = \
	$(top_builddir)/src/xmlpull/libwsdlpullxml.la \
	$(top_builddir)/src/schemaparser/libwsdlpullschema.la

