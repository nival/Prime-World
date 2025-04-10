@echo off
cd ..\..
Vendor\BuildUtils\FixSln2008.exe PF_FixSln.config --sync
cd Vendor\BuildUtils