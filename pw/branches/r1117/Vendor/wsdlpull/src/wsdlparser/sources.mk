wsdl_h_sources = \
	$(top_srcdir)/src/wsdlparser/WsdlParser.cpp \
	$(top_srcdir)/src/wsdlparser/WsdlDebug.cpp \
	$(top_srcdir)/src/wsdlparser/Message.cpp \
	$(top_srcdir)/src/wsdlparser/WsdlElement.cpp \
	$(top_srcdir)/src/wsdlparser/WsdlInvoker.cpp \
	$(top_srcdir)/src/wsdlparser/Soap.cpp
wsdl_cc_sources = \
	$(top_srcdir)/src/wsdlparser/WsdlParser.h \
	$(top_srcdir)/src/wsdlparser/WsdlException.h \
	$(top_srcdir)/src/wsdlparser/WsdlExtension.h \
	$(top_srcdir)/src/wsdlparser/WsdlElement.h \
	$(top_srcdir)/src/wsdlparser/WsdlInvoker.h \
	$(top_srcdir)/src/wsdlparser/Soap.h \
	$(top_srcdir)/src/wsdlparser/Message.h \
	$(top_srcdir)/src/wsdlparser/Operation.h \
	$(top_srcdir)/src/wsdlparser/PortType.h \
	$(top_srcdir)/src/wsdlparser/Binding.h \
	$(top_srcdir)/src/wsdlparser/Service.h
