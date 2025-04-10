## examples/print
## This is the input file for automake, which will generate Makefile.in ##

MAINTAINERCLEANFILES = Makefile.in

#
bin_PROGRAMS = print

print_SOURCES = print.cpp
print_CPPFLAGS = -DSCHEMADIR=\"$(datadir)/wsdlpull/\"
print_LDFLAGS = \
	$(top_builddir)/src/wsdlparser/libwsdlpull.la \
	$(top_builddir)/src/schemaparser/libwsdlpullschema.la \
	$(top_builddir)/src/xmlpull/libwsdlpullxml.la

#
docsdir = $(prefix)/docs
docs_DATA = README_print.txt

EXTRA_DIST = $(docs_DATA)

