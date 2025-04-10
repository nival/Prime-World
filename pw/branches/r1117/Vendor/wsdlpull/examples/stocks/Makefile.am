## examples/stocks 
## This is the input file for automake, which will generate Makefile.in ##

MAINTAINERCLEANFILES = Makefile.in

#
bin_PROGRAMS = stocks

stocks_SOURCES = stocks.cpp
stocks_CPPFLAGS = -DSCHEMADIR=\"$(datadir)/wsdlpull/\"
stocks_LDFLAGS = \
	$(top_builddir)/src/wsdlparser/libwsdlpull.la \
	$(top_builddir)/src/schemaparser/libwsdlpullschema.la \
	$(top_builddir)/src/xmlpull/libwsdlpullxml.la

