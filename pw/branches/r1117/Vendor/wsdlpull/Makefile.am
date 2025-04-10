## wsdlpull top directory
include $(top_srcdir)/Makefile.common

ACLOCAL_AMFLAGS = -I config

AUTOMAKE_OPTIONS = dist-bzip2

MAINTAINERCLEANFILES = Makefile.in aclocal.m4 configure \
			src/config-h.in config/stamp-h.in

if EXAMPLES
SUBDIRS = src tests docs man win32 examples
else
SUBDIRS = src tests docs man win32
endif

docsdir = $(datadir)/wsdlpull
docs_DATA = wsdlpull.html README

EXTRA_DIST = AUTHORS COPYING CHANGES $(docs_DATA)

#pkginclude_HEADERS = src/config.h
pkgincludedir= $(includedir)

