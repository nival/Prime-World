<?xml version="1.0" encoding="utf-8"?>
<!-- New document created with EditiX at Tue Jul 03 11:41:25 MSD 2012 -->
<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html" />
  <xsl:template match="/">
    <html>
      <body>
        <table border="1">
         <tr>
          <th>Name</th>
          <th>Protect</th>
          <th>Type</th>
          <th>Speed</th>
          <th>RemoveFromExports</th>
          <!--<th>EnableCallProtection</th>-->
          <th>DeleteFunctionArgsNames</th>
         </tr>
        <xsl:apply-templates select="/Settings/Protection/OutputFiles/file/Functions/function">
          <xsl:sort select="Name" />
        </xsl:apply-templates>
        </table>
      </body>
    </html>
  </xsl:template>
  <xsl:template match="function">
    <tr><td><xsl:value-of select="Name" /></td><td><xsl:value-of select="ProtectOptions/Protect" /></td><td><xsl:value-of select="ProtectOptions/Type" /></td><td><xsl:value-of select="ProtectOptions/Speed" /></td><td><xsl:value-of select="ProtectOptions/RemoveFromExports" /></td><!--<td><xsl:value-of select="ProtectOptions/EnableCallProtection" /></td>--><td><xsl:value-of select="ProtectOptions/ManagedProtectionOptions/DeleteFunctionArgsNames" /></td></tr>
  </xsl:template>
</xsl:stylesheet>
