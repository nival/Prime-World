@echo off
if "%1"=="" goto noparam

PerformanceLog.rb -fia %1 > %~n1-flat.txt
PerformanceLog.rb -fina %1 > %~n1-flat-nostl.txt
PerformanceLog.rb -final %1 > %~n1-flat-nostl-nolines.txt
PerformanceLog.rb -a %1 > %~n1-tree.txt
PerformanceLog.rb -al %1 > %~n1-tree-nolines.txt
exit

:noparam
echo "usage: %~nx0 <performance.txt>"
