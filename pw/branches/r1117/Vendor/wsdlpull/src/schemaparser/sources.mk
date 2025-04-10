schema_h_sources = \
	$(top_srcdir)/src/schemaparser/SchemaParser.h \
	$(top_srcdir)/src/schemaparser/SchemaValidator.h \
	$(top_srcdir)/src/schemaparser/XSDType.h \
	$(top_srcdir)/src/schemaparser/SimpleType.h \
	$(top_srcdir)/src/schemaparser/ComplexType.h \
	$(top_srcdir)/src/schemaparser/TypeContainer.h \
	$(top_srcdir)/src/schemaparser/Element.h \
	$(top_srcdir)/src/schemaparser/Attribute.h \
	$(top_srcdir)/src/schemaparser/SchemaParserException.h \
	$(top_srcdir)/src/schemaparser/TypesTable.h \
	$(top_srcdir)/src/schemaparser/Schema.h \
	$(top_srcdir)/src/schemaparser/Group.h \
	$(top_srcdir)/src/schemaparser/ContentModel.h \
	$(top_srcdir)/src/schemaparser/AttributeGroup.h \
	$(top_srcdir)/src/schemaparser/Constraint.h \
	$(top_srcdir)/src/schemaparser/Annotation.h
schema_cc_sources = \
	$(top_srcdir)/src/schemaparser/SchemaParser.cpp \
	$(top_srcdir)/src/schemaparser/SchemaValidator.cpp \
	$(top_srcdir)/src/schemaparser/SimpleType.cpp \
	$(top_srcdir)/src/schemaparser/ComplexType.cpp \
	$(top_srcdir)/src/schemaparser/TypesTable.cpp \
	$(top_srcdir)/src/schemaparser/TypeContainer.cpp \
	$(top_srcdir)/src/schemaparser/SchemaDebug.cpp \
	$(top_srcdir)/src/schemaparser/Group.cpp \
	$(top_srcdir)/src/schemaparser/ContentModel.cpp
