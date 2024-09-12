@echo off
set SEL_NAME=%1
python main.py %SEL_NAME%.graph %SEL_NAME%.csv --main %2 %3 %4 %5 %6 
rem --log_users --details
"C:\Tools\Graphviz\bin\dot.exe" -Tsvg %SEL_NAME%.graph -o%SEL_NAME%.svg