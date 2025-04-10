# Microsoft Developer Studio Project File - Name="wsdlpull" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=wsdlpull - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wsdlpull.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wsdlpull.mak" CFG="wsdlpull - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wsdlpull - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "wsdlpull - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wsdlpull - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "wsdlpull - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /w /W0 /Gm /GX /ZI /Od /I "..\src\\" /I "." /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "wsdlpull - Win32 Release"
# Name "wsdlpull - Win32 Debug"
# Begin Group "wsdlparser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\wsdlparser\Binding.h
# End Source File
# Begin Source File

SOURCE=..\src\wsdlparser\Message.cpp
# End Source File
# Begin Source File

SOURCE=..\src\wsdlparser\Message.h
# End Source File
# Begin Source File

SOURCE=..\src\wsdlparser\Operation.h
# End Source File
# Begin Source File

SOURCE=..\src\wsdlparser\PortType.h
# End Source File
# Begin Source File

SOURCE=..\src\wsdlparser\Service.h
# End Source File
# Begin Source File

SOURCE=..\src\wsdlparser\Soap.cpp
# End Source File
# Begin Source File

SOURCE=..\src\wsdlparser\Soap.h
# End Source File
# Begin Source File

SOURCE=..\src\wsdlparser\WSDLDebug.cpp
# End Source File
# Begin Source File

SOURCE=..\src\wsdlparser\WsdlElement.cpp
# End Source File
# Begin Source File

SOURCE=..\src\wsdlparser\WsdlElement.h
# End Source File
# Begin Source File

SOURCE=..\src\wsdlparser\WSDLException.h
# End Source File
# Begin Source File

SOURCE=..\src\wsdlparser\WSDLExtension.h
# End Source File
# Begin Source File

SOURCE=..\src\wsdlparser\WsdlInvoker.cpp
# End Source File
# Begin Source File

SOURCE=..\src\wsdlparser\WsdlInvoker.h
# End Source File
# Begin Source File

SOURCE=..\src\wsdlparser\WSDLParser.cpp
# End Source File
# Begin Source File

SOURCE=..\src\wsdlparser\WSDLParser.h
# End Source File
# End Group
# Begin Group "schemaparser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\schemaparser\Attribute.h
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\AttributeGroup.h
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\ComplexType.cpp
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\ComplexType.h
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\Constraint.h
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\ContentModel.cpp
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\ContentModel.h
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\Element.h
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\Group.cpp
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\Group.h
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\Schema.h
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\SchemaDebug.cpp
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\SchemaParser.cpp
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\SchemaParser.h
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\SchemaParserException.h
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\SchemaValidator.cpp
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\SchemaValidator.h
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\SimpleType.cpp
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\SimpleType.h
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\TypeContainer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\TypeContainer.h
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\TypesTable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\TypesTable.h
# End Source File
# Begin Source File

SOURCE=..\src\schemaparser\XSDType.h
# End Source File
# End Group
# Begin Group "xmlpull"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\xmlpull\ConfigFile.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xmlpull\ConfigFile.h
# End Source File
# Begin Source File

SOURCE=..\src\xmlpull\osdir.h
# End Source File
# Begin Source File

SOURCE=..\src\xmlpull\Qname.h
# End Source File
# Begin Source File

SOURCE=.\w3c.cpp
# End Source File
# Begin Source File

SOURCE=.\w3c.h
# End Source File
# Begin Source File

SOURCE=..\src\xmlpull\XmlPullParser.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xmlpull\XmlPullParser.h
# End Source File
# Begin Source File

SOURCE=..\src\xmlpull\XmlPullParserException.h
# End Source File
# Begin Source File

SOURCE=..\src\xmlpull\XmlSerializer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xmlpull\XmlSerializer.h
# End Source File
# Begin Source File

SOURCE=..\src\xmlpull\XmlUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xmlpull\XmlUtils.h
# End Source File
# End Group
# End Target
# End Project
