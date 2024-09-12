<?xml version="1.0" encoding="UTF-8"?>
<xsl:transform version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:param name="build"/>
  <xsl:param name="revision"/>
  <xsl:param name="line"/>
  <xsl:param name="culture"/>
	<xsl:output method="text"/>
	<xsl:template match="/">PWSOC_VERSION_HIGH = <xsl:value-of select="Product/Version/Major"/>
PWSOC_VERSION_MED = <xsl:value-of select="Product/Version/Minor"/>
PWSOC_VERSION_LOW = <xsl:value-of select="Product/Version/Patch"/>
PWSOC_VERSION_REVISION = <xsl:value-of select="$revision"/>
PWSOC_BRANCH_NAME = "<xsl:value-of select="Product/Version/Branch"/>"
	</xsl:template>
</xsl:transform>
