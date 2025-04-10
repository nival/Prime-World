@echo off
set xmlswf="xmlswf"
set converter="xmlswf\swfmill.exe"

set name=main
%converter% -v swf2xml "%name%.swf" "%xmlswf%\%name%.swf.xml"

set name=selectFraction
%converter% -v swf2xml "%name%.swf" "%xmlswf%\%name%.swf.xml"

set name=loginQueue
%converter% -v swf2xml "%name%.swf" "%xmlswf%\%name%.swf.xml"