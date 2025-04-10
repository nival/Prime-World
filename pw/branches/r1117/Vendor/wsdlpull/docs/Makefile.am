# docs
#
include $(top_srcdir)/src/xmlpull/sources.mk
include $(top_srcdir)/src/wsdlparser/sources.mk
include $(top_srcdir)/src/schemaparser/sources.mk
include $(top_srcdir)/src/tools/sources.mk

MAINTAINERCLEANFILES = Makefile.in

docdir = @docdir@

html_tarname = @PACKAGE_TARNAME@-doc-@PACKAGE_VERSION@

noinst_DATA = doxy.conf
EXTRA_DIST = $(noinst_DATA)

# Targets
all-local: html-local

html-local: html/index.html

html/index.html: doxy.conf \
	$(xmlpull_h_sources) $(xmlpull_cc_sources) \
	$(wsdl_h_sources) $(wsdl_cc_sources) \
	$(schema_h_sources) $(schema_cc_sources) \
	$(wsdltool_cc_sources) $(schematool_cc_sources)
	doxygen $<

dist-html: html-local
	cp -a $(top_builddir)/docs/html $(top_builddir)/$(html_tarname)
	tar chof - $(top_builddir)/$(html_tarname) | \
		gzip --best -c > $(top_builddir)/$(html_tarname).tar.gz
	tar chof - $(top_builddir)/$(html_tarname) | \
		bzip2 -9 -c > $(top_builddir)/$(html_tarname).tar.bz2
	rm -rf $(top_builddir)/$(html_tarname)

install-data-local: html-local
	$(mkinstalldirs) $(DESTDIR)$(docdir)
	if test -d html; then \
		$(mkinstalldirs) $(DESTDIR)$(docdir)/html; \
		for f in html/*; do \
			$(INSTALL_DATA) $$f $(DESTDIR)$(docdir)/html; \
		done \
	fi

uninstall-local:
	rm -rf $(DESTDIR)$(docdir)

clean-local:
	rm -rf html *.log *.tag

