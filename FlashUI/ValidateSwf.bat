@echo off
ECHO generate xml
call Swf2Xml.bat
ECHO generate and validate swf
call GenerateAndValidateBytes.bat
Exit
